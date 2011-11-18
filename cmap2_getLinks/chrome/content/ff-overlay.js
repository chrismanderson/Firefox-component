cmap2_getlinks.onFirefoxLoad = function(event) {
  document.getElementById("contentAreaContextMenu")
          .addEventListener("popupshowing", function (e){ cmap2_getlinks.showFirefoxContextMenu(e); }, false);
};

cmap2_getlinks.showFirefoxContextMenu = function(event) {
  // show or hide the menuitem based on what the context menu is on
  document.getElementById("context-cmap2_getlinks").hidden = gContextMenu.onImage;
};

window.addEventListener("load", cmap2_getlinks.onFirefoxLoad, false);
