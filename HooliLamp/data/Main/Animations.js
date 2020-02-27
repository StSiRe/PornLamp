function Animations()   {
    ClearElements();
    var main = document.getElementById("main");
    var fragment = document.createDocumentFragment();
    fragment.appendChild(CreateForm(
        Separator(),
        CreateImage("Animations"),
        Separator(),
        CreateText("Powee Mode:"),
        CreateToogleButton("PowerMode","PowerModeButton()"),
        Separator(),
        
        CreateWrapper(
            CreateImage("Animations/Brightness"),
            CreateProgressBar("Brightness","SetBrightness()")
        )
    ));    
    main.appendChild(fragment);
}
function CreateWrapper(...childs)
{
    var div = document.createElement("div");
    div.classList.add("wrapper");
    div.appendChild(childs[0]);
    div.appendChild(childs[1]);
    return div;
}
function SetBrightness()
{
    var element = document.getElementById("Brightness");
    var value = element.value;
    alert(value);
}
function PowerModeButton()
{
    var button = document.getElementById("PowerMode");
    if(button.checked)
    {        
        alert("On"); 
    }
    else
    {
        alert("Off");
    }
}
///Очищает полностью экран от элементов
function ClearElements()
{
    var main = document.getElementById("main");
    main.remove();
    var doc = document.createElement("div");
    doc.setAttribute("id","main");
    var page = document.getElementsByClassName("page");
    page[0].appendChild(doc);
}

function CreateProgressBar(id,onClickHandler)
{
    var div = document.createElement("input");
    div.classList.add("progress");
    div.setAttribute("oninput",onClickHandler);
    div.type = "range";
    div.min = "0";
    div.max = "100";
    return div;
}
function CreateText(text)   {
    var div = document.createElement("text");
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
function CreateImage(path)  {
    if(path == null){
        return null;
    }        
    var div = document.createElement("div");
    div.className="image";
    var div1 = document.createElement("img");
    div1.src = "Images/"+ path + ".png";
    div.appendChild(div1);
    return div;
}