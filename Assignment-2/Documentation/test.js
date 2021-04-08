function saveTextAsFile(){  
    var textToSave = document.getElementById("inputTextToSave").value;
    var textToSaveAsBlob = new Blob([textToSave], {type:"text/plain"});
    var textToSaveAsURL = window.URL.createObjectURL(textToSaveAsBlob);
    var fileNameToSaveAs = document.getElementById("inputFileNameToSaveAs").value;
    var downloadLink = document.createElement("a");
    downloadLink.download = fileNameToSaveAs;
    downloadLink.innerHTML = "Download File";
    downloadLink.href = textToSaveAsURL;
    downloadLink.onclick = destroyClickedElement;
    downloadLink.style.display = "none";
    document.body.appendChild(downloadLink);
    downloadLink.click();
  }
  function destroyClickedElement(event){
    document.body.removeChild(event.target);
  }
  var loadFile = function(event) {
      var image = document.getElementById('tcoutput');
      image.src = URL.createObjectURL(event.target.files[0]);
  };
    function TestRun(){
    alert('running testcase');; 
    var textToRun = document.getElementById("fileNameToRunAs").value; 
    var objShell = new ActiveXObject("WSCRIPT.Shell").Run("cmd.exe /k cd C:/Users/Abhishek/Desktop/DAA/Assignment-1/html/test & python plot.py "+textToRun);
    alert('finished visualization');; 
  }