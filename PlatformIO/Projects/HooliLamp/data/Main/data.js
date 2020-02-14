
function Animations()   {
    ClearElements();
    var main = document.getElementById("main");
    var fragment = document.createDocumentFragment();
    fragment.appendChild(CreateForm(
        Separator(),
        CreateImage("Animations"),
        Separator(),
        CreateText("State: "),
        CreateToogleButton("11","BOC()")  ,
        Separator()
    ));    
    main.appendChild(fragment);
}

function BOC()
{
    
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
    div.setAttribute("onclick",onClickHandler);
    var div1 = document.createElement("input");
    div1.type = "checkbox";
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