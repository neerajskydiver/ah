
/* Ninja Slider Video Plugin v2014.1.11. Copyright www.menucool.com */

var McVideo2=function(){var a=[],b=function(b,e){if(!b.vPlayer)for(var c=0;c<a.length;c++){var d=new a[c](b,e);if(typeof d.play!=="undefined"){b.vPlayer=d;break}}};return{plugin:function(b){a.push(b)},register:function(c,a){b(c,a)},play:function(a,e,d,c){if(a.vPlayer){var b=a.vPlayer.play(a,e,d,c);if(b==1)return 1}return 0},stop:function(a){a.vPlayer&&a.vPlayer.stop(a)}}}(),VimeoPlayer2=function(a,c){if(a.nodeName!="A"||a.getAttribute("href").toLowerCase().indexOf("vimeo.com")==-1)return null;var b=function(){var a;if(window.addEventListener)window.addEventListener("message",b,false);else window.attachEvent("onmessage",b,false);function b(b){try{var a=JSON.parse(b.data);switch(a.event){case"ready":e();break;case"finish":d()}}catch(b){}}function f(e,b){var c={method:e};if(b!==undefined)c.value=b;if(window.JSON){var d=a.contentWindow||a.contentDocument;d.postMessage(window.JSON.stringify(c),a.getAttribute("src").split("?")[0])}}function e(){f("addEventListener","finish")}function d(){c.To(1)}return{setIframe:function(b){a=b}}},e=new b;function d(a,k,j,f){if(!a.children.length){var h="&loop=0&autoplay=1&wmode=opaque&color=bbbbbb&"+(new Date).getTime(),d=a.getAttribute("href"),i=d.toLowerCase().indexOf("vimeo.com"),c='<iframe id="mcVideo'+f+'" src="http://player.vimeo.com/video/'+d.substring(i+10)+"?api=1&player_id=mcVideo"+f+h+'" webkitAllowFullScreen mozallowfullscreen allowFullScreen';c+=' frameborder="0" width="'+k+'" height="'+j+'" style="position:absolute;top:0;left:0;"></iframe>';var b=document.createElement("span");b.innerHTML=c;var g=b.childNodes[0];a.appendChild(g);e.setIframe(g)}return 1}return{play:function(b,e,c,a){return d(b,e,c,a)},stop:function(a){a.innerHTML=""}}};McVideo2.plugin(VimeoPlayer2);var YoutubePlayer2=function(b,a){if(b.nodeName!="A"||b.getAttribute("href").toLowerCase().indexOf("youtube.com")==-1)return null;var c=function(){var e=document.createElement("script");e.src="http://www.youtube.com/player_api";var c=document.getElementsByTagName("script")[0];c.parentNode.insertBefore(e,c);var h,i,d=0,b=function(a){if(typeof YT!=="undefined"&&typeof YT.Player!=="undefined")h=new YT.Player(a,{events:{onReady:g,onStateChange:f}});else if(d<30){setTimeout(function(){b(a)},50);d++}};function f(b){if(b.data==0){console.log(a,typeof a);a.To(1)}}function g(){}return{setPlayer:function(a){b(a)}}},e=new c;function d(a,k,j,d){if(!a.children.length){var f="&loop=0&start=0&wmode=opaque&html5=1&autohide=1&showinfo=0&iv_load_policy=3&allowScriptAccess=always&modestbranding=1&showsearch=0",c=a.getAttribute("href"),h=c.toLowerCase().indexOf("v="),g='<iframe id="mcVideo'+d+'" src="http://www.youtube.com/embed/'+c.substring(h+2)+"?enablejsapi=1&autoplay=1"+f+'" frameborder="0" width="'+k+'" height="'+j+'" style="position:absolute;top:0;left:0;"></iframe>',b=document.createElement("span");b.innerHTML=g;var i=b.childNodes[0];a.appendChild(i);e.setPlayer("mcVideo"+d)}return 1}return{play:function(b,e,c,a){return d(b,e,c,a)},stop:function(a){a.innerHTML=""}}};McVideo2.plugin(YoutubePlayer2)