(function(){
  function dsr(results, store){
    var sr = document.getElementById('search-results');
    if (results.length){
      var appendString = '';
      for (var i = 0; i < results.length; i++){
        var item = store[results[i].ref];
        appendString += '<div class="col-xs-12 col-sm-4 col-md-4 col-lg-4"><div class="box card">'+
          '<a href="'+item.url+'">'+'<div class="frame"><img src="'+item.imgsrc+'" alt="'+item.imgalt+'"></div><h3>'+
          item.title+'</h3></a></div></div>'} 
      sr.innerHTML += appendString;}
    else{
      sr.innerHTML += '<h3>No results found</h3>';
    }
  }
  function getQueryVariable(variable){
    var query = window.location.search.substring(1);
    var vars = query.split('&');
    for (var i = 0; i < vars.length; i++){
      var pair = vars[i].split('=');
      if (pair[0] === variable) {
        return decodeURIComponent(pair[1].replace(/\+/g, '%20'));
      }
    }
  }
  var searchTerm = getQueryVariable('query');
  if (searchTerm){
    document.getElementById('search-box').setAttribute("value", searchTerm);
    var idx = lunr(function(){this.field('id');
      this.field('slug');
      for (var key in window.store){
        this.add({'id': key,'slug': window.store[key].slug});
      }
    }
    );
    var results = idx.search(searchTerm + "~1");dsr(results, window.store);
  }
})();
