function CreateButtonImage(path,onClick)  {
    if(path == null){
        return null;
    }        
    var div = document.createElement("div");
    div.setAttribute("onclick",onClick);
    var div1 = document.createElement("img");
    div1.src = "Images/"+ path + ".svg";
    div.appendChild(div1);
    return div;
}
function CreateButtonImageWithID(path,onClick,id)  {
    if(path == null){
        return null;
    }        
    var div = document.createElement("div");
    div.id = id;
    div.setAttribute("onclick",onClick);
    var div1 = document.createElement("img");
    div1.src = "Images/"+ path + ".svg";
    div.appendChild(div1);
    return div;
}
function CreateImage(path)  {
    if(path == null){
        return null;
    }        
    var div1 = document.createElement("img");
    div1.src = "Images/"+ path + ".svg";
    return div1;
}
function CreateImageWithID(path,id)  {
    if(path == null){
        return null;
    }        
    var div1 = document.createElement("img");
    div1.id = id;
    div1.src = "Images/"+ path + ".svg";
    return div1;
}
function CreateProgressBar(id,onClickHandler)
{
    var div = document.createElement("input");
    div.classList.add("progress");
    div.id = id;
    div.setAttribute("onmouseup",onClickHandler);
    div.type = "range";
    div.min = "0";
    div.max = "100";
    return div;
}
function CreateText(text)   {
    var div = document.createElement("text");
    div.classList.add("text");
    div.innerText = text;
    return div
}

function Separator()   {
    var div = document.createElement("p");
    return div
}
//Получает свой собственный id, и ссылку на обработкик взаимодействия
function CreateToogleButton(id,onClickHandler) {
    var div = document.createElement("label");
    div.classList.add("switch");
    div.id = id;
    
    var div1 = document.createElement("input");
    div1.type = "checkbox";
    div1.setAttribute("onclick",onClickHandler);
    var div2 = document.createElement("span");
    div2.classList.add("slider","round");
    div.appendChild(div1);
    div.appendChild(div2);
    return div;
}
function CreateForm(...childs) {
    var div = document.createElement("div");
    div.className="form";
    if(childs != null){
        for (let index = 0; index < childs.length; index++) {
            div.appendChild(childs[index]);            
        }
    }
    return div;
}
function CreateFormLeft(...childs) {
    var div = document.createElement("div");
    div.className="leftElement";
    if(childs != null){
        for (let index = 0; index < childs.length; index++) {
            div.appendChild(childs[index]);            
        }
    }
    return div;
}
function CreateFormRight(...childs) {
    var div = document.createElement("div");
    div.className="rightElement";
    if(childs != null){
        for (let index = 0; index < childs.length; index++) {
            div.appendChild(childs[index]);            
        }
    }
    return div;
}
function CreateSelect(id,onClickHandler,...options)
{
    var div = document.createElement("select");
    div.classList.add("select");   
    div.id = id; 
    div.setAttribute("onchange",onClickHandler);
    //if(options == undefined)
    //    return div;
    for(var i=0;i<options.length;i++)
    {        
        var doc = document.createElement("option");
        doc.value = options[i];
        div.classList.add("option");
        div.appendChild(doc);
    }
    return div;
}

function CreateWrapper(...childs)
{
    var div = document.createElement("div");
    div.classList.add("wrapper");
    for(var i=0;i<childs.length;i++)
    {        
        div.appendChild(childs[i]);
    }
    return div;
}
function CreateBackButton()
{
    var div = document.createElement("div");
    div.classList.add("back_button");
    var div1 = document.createElement("img");
    div1.classList.add("back_button_image");
    div1.src = "Images/Return.svg";
    div.appendChild(div1);
    div.onclick = ()=>{
        MainPage();    
    };
    return div;
}
function ClearChilds(node)
{
    while (node.firstChild) {
        node.removeChild(node.firstChild);
    }
    return node;
}