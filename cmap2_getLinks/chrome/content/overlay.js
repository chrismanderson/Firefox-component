var cmap2_getlinks = {
  onLoad: function() {
    // initialization code
    this.initialized = true;
    this.strings = document.getElementById("cmap2_getlinks-strings");
  },

  onMenuItemCommand: function(e) {
    var promptService = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                                  .getService(Components.interfaces.nsIPromptService);

  try {
	  
	  // creates the component 
	  var obj = Components.classes["@mozilla.org/simple;1"].createInstance(Components.interfaces.nsISimple);	
	  
	  // gets the DOM document ready to be sent to the component
	  var browser = gBrowser.mCurrentBrowser;
	  var doc = browser.contentDocument;
	  
	  // initializes the arrays for the return values
	  var numLinks = {};
	  var numImages = {};

      // makes the call to the component
	  var result = obj.saveSummary(doc,numLinks,numImages);

      // opens the results window
	  window.openDialog("chrome://cmap2_getlinks/content/alert.xul", "newWindow", "chrome,centerscreen",numLinks, numImages, result);
  }
  catch (e) { alert(e); }
  },

  onToolbarButtonCommand: function(e) {

    cmap2_getlinks.onMenuItemCommand(e);
  }
};

window.addEventListener("load", cmap2_getlinks.onLoad, false);
