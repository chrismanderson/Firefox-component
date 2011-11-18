#include <stdio.h>
#include "nsSimple.h"
#include "nsMemory.h"
#include "nsCOMPtr.h"
#include "nsISupportsUtils.h"
#include "nsStringAPI.h"
#include "nsIServiceManager.h"
#include "nsILocalFile.h"
#include "nsIFile.h"
#include "nsIFactory.h"
#include "nsIInputStream.h"
#include "nsISafeOutputStream.h"
#include "nsIOutputStream.h"
#include "nsDirectoryServiceDefs.h"
#include "nsDirectoryServiceUtils.h"
#include "nsComponentManagerUtils.h"
#include "nsError.h"
#include "nsIFileStreams.h"
#include "nsNetUtil.h"
#include "nsIConverterOutputStream.h"
#include "nsIProperties.h"

// include any of the other classes we reference
#include "nsIDocument.h"
#include "nsIDOMNodeList.h"
#include "nsIDOMNode.h"
#include "nsIDOMHTMLAnchorElement.h"
#include "nsIDOMHTMLImageElement.h"


NS_IMPL_ISUPPORTS1(SimpleImpl, nsISimple)

//
// nsSimpleImpl ctor
//
SimpleImpl::SimpleImpl()
{
 NS_INIT_ISUPPORTS();
}

//
// nsSimpleImpl dtor
//
SimpleImpl::~SimpleImpl()
{
  // nothing
}


NS_IMETHODIMP
SimpleImpl::SaveSummary(nsIDOMDocument* inDoc, PRUint32* numLinks, PRUint32* numImages, PRBool* outSuccess)
{
	nsCOMPtr<nsIDOMNodeList> nodeAList;
	nsCOMPtr<nsIDOMNodeList> nodeIMGList;
	
	PRUint32 nodeASize;
	PRUint32 nodeIMGSize;
	
	// Gets the count of both A and IMG tags and stores the number in the out paramters.
	inDoc->GetElementsByTagName(NS_LITERAL_STRING("A"),getter_AddRefs(nodeAList));
	inDoc->GetElementsByTagName(NS_LITERAL_STRING("IMG"),getter_AddRefs(nodeIMGList));
	nodeAList->GetLength(&nodeASize);
	nodeIMGList->GetLength(&nodeIMGSize);
	
	*numLinks = nodeASize;
	*numImages = nodeIMGSize;
	
	// declares some variables to be used later
	nsAutoString temp;
	nsAutoString imgtemp;
	nsAutoString fileName;
	nsAutoString path;
	
	// Gets the service to generate the cross-platform 'Desktop' folder
	nsCOMPtr<nsIProperties> dirService
	    (do_GetService("@mozilla.org/file/directory_service;1"));
	
	// declares the pointer/value to get the 'Desktop' directory
	nsCOMPtr<nsIFile> dbFile;
	nsAutoString aPath;
	
	// Gets the path, validates that it was successful
	nsresult rv = NS_GetSpecialDirectory("Desk", getter_AddRefs(dbFile));
	
	if (NS_FAILED(rv)) {
		*outSuccess = PR_FALSE;
		return NS_OK;
	}
	
	dbFile->GetPath(aPath);
	
	// Gets the name of the file and appends the .txt extension
	inDoc->GetTitle(fileName);
	fileName.AppendASCII(".txt");
	
	// Appends the filename to the path of Desktop
	aPath.AppendASCII("/");
	aPath.Append(fileName);
    
    // Tests opening a file at the computed path/name
    FILE *pFile;
	printf("%s stuff here", NS_LossyConvertUTF16toASCII(aPath).get());
    pFile = fopen (NS_LossyConvertUTF16toASCII(aPath).get(), "r");
    
	if (pFile != NULL) {		
		*outSuccess = PR_FALSE;
		fclose(pFile);
		printf("file exists");
	}
	
	else {
		// opens the file
		pFile = fopen (NS_LossyConvertUTF16toASCII(aPath).get(), "w");
		
		// starts the two loops to store the text in the file
		if (pFile != NULL) {
			fputs("Links\n", pFile);
			fputs("=====\n", pFile);
			for (PRUint32 i = 0; i < nodeASize; i++) {
				nsCOMPtr<nsIDOMNode> node;
				nodeAList->Item(i,getter_AddRefs(node));
				nsCOMPtr<nsIDOMHTMLAnchorElement> link = do_QueryInterface(node);
				link->GetHref(temp);
		        fputs(NS_LossyConvertUTF16toASCII(temp).get(), pFile);
				fputs("\n", pFile);
			}
	
			fputs("\nImages\n", pFile);
			fputs("======\n", pFile);
			for (PRUint32 i = 0; i < nodeIMGSize; i++) {
				nsCOMPtr<nsIDOMNode> imgnode;
				nodeIMGList->Item(i,getter_AddRefs(imgnode));
				nsCOMPtr<nsIDOMHTMLImageElement> image = do_QueryInterface(imgnode);
				image->GetSrc(imgtemp);
				fputs(NS_LossyConvertUTF16toASCII(imgtemp).get(), pFile);
				fputs("\n", pFile);
			}
		}
    
    	fclose(pFile);
		*outSuccess = PR_TRUE;
	}
	return NS_OK;
}


//***************************************************************
//***************************************************************

//
// Module info
//
// Most examples have the module in a separate file, but there's no
// need to do that. Change the macros and class names to reference
// your own class.
//

#define MOZILLA_INTERNAL_API 1

#include "mozilla/ModuleUtils.h"
#include "nsIServiceManager.h"
#include "nsICategoryManager.h"

// Define the constructor function for the objects
NS_GENERIC_FACTORY_CONSTRUCTOR(SimpleImpl)

NS_DEFINE_NAMED_CID(NS_SIMPLE_CID);

static const mozilla::Module::CIDEntry kPermissionsCIDs[] = {
  { &kNS_SIMPLE_CID, false, NULL, SimpleImplConstructor },
  { NULL }
};

static const mozilla::Module::ContractIDEntry kPermissionsContracts[] = {
  { NS_SIMPLE_PROG_ID, &kNS_SIMPLE_CID },
  { NULL }
};

static const mozilla::Module::CategoryEntry kPermissionsCategories[] = {
  { XPCOM_DIRECTORY_PROVIDER_CATEGORY, "simple", NS_SIMPLE_PROG_ID },
  { NULL }
};

static const mozilla::Module kPermissionsModule = {
  mozilla::Module::kVersion,
  kPermissionsCIDs,
  kPermissionsContracts,
  kPermissionsCategories
};

NSMODULE_DEFN(nsPermissionsModule) = &kPermissionsModule;


