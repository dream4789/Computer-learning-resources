console.log('write begin');
document.write('<script src="try_1.js" onreadystatechange="console.log(\'file 1 callback \',this.readyState,\' IE\');" onload="if(!document.all){console.log(\'file 1 callback,NOT IE \');}"><\/script>');
document.write('<script src="try_2.js" onreadystatechange="console.log(\'file 2 callback \',this.readyState,\' IE\');" onload="if(!document.all){console.log(\'file 2 callback,NOT IE \');}"><\/script>');
console.log('write finished');