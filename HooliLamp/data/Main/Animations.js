var AnimationsEffects;
var Brightness;
var CurrentAnimation;
function Animations()   {
    ClearElements();
    var main = document.getElementById("main");
    var fragment = document.createDocumentFragment();
    fragment.appendChild(CreateForm(
        Separator(),
        CreateImage("Animations"),
        Separator(),
        CreateText("PowerState:"),
        CreateToogleButton("PowerState","PowerStateButton()"),
        Separator(),
        
        CreateWrapper(
            CreateImage("Brightness"),
            CreateProgressBar("Brightness","SetBrightness()")
        ),
        Separator(),
        CreateWrapper(
            CreateButtonImage("previous","PreviousAnimation()"),
            CreateSelect("AnimationsList","ChangeAnimation()",null),
            CreateButtonImage("next","NextAnimation()")
        )
    ));    
    main.appendChild(fragment);
    LoadData();
}

function ChangeAnimation()
{
    var div = document.getElementById("AnimationsList");
    var xhr = new XMLHttpRequest();
    xhr.open('GET', '/Animations/Animation?Animation=' + div.value, false);
    xhr.send();
}
function NextAnimation()
{
    var div = document.getElementById("AnimationsList");
    div.selectedIndex++;
    if(div.value == "")
    {
        div.selectedIndex = 0;
    }
    var xhr = new XMLHttpRequest();
    xhr.open('GET', '/Animations/Animation?Animation=' + div.value, false);
    xhr.send();
}
function PreviousAnimation()
{
    var div = document.getElementById("AnimationsList");
    div.selectedIndex--;
    
    if(div.value == "")
    {
        div.selectedIndex = AnimationsEffects.length - 1;
    }
    var xhr = new XMLHttpRequest();
    xhr.open('GET', '/Animations/Animation?Animation=' + div.value, false);
    xhr.send();
}
function LoadData()
{
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (this.status == 200) {
            var data = JSON.parse(this.responseText);
            AnimationsEffects = data.AnimationsList;
            Brightness = data.Brightness / 256 * 100;
            CurrentAnimation = data.CurrentAnimation;
            var div = document.getElementById("Brightness");
            div.value = Brightness;

            div = document.getElementById("PowerState");
            if(Brightness > 0)
            {                
                div.control.checked = true;
            }
            else
            {
                div.control.checked = false;
            }
                        
            div = document.getElementById("AnimationsList");
            div.removeChild(div.childNodes[0]);
            for(var i=0;i<AnimationsEffects.length;i++)
            {
                var option = document.createElement("option");
                option.text = AnimationsEffects[i];
                div.appendChild(option);
            } 
            for(var i=0;i<AnimationsEffects.length;i++)
            {
                if(CurrentAnimation == AnimationsEffects[i])
                {
                    div.selectedIndex = i;
                }
            }
        }
    };
    xhr.open('GET', '/Animations/Data', false);

    xhr.send();
}
function SetBrightness()
{
    var element = document.getElementById("Brightness");
    var value = element.value;
    var xhr = new XMLHttpRequest();

    xhr.open('GET', '/Animations/Brightness?Brightness=' + value, false);

    xhr.send();
}
function PowerStateButton()
{
    var button = document.getElementById("PowerState");
    var res = "";
    if(button.control.checked)
        res = "On";
    else
        res = "Off";
    
    var xhr = new XMLHttpRequest();

    xhr.open('GET', '/Animations/PowerState?'+ "PowerState" + '=' + res, false);

    xhr.send();
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
    div.id = id;
    div.setAttribute("onmouseup",onClickHandler);
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
function CreateButtonImage(path,onClick)  {
    if(path == null){
        return null;
    }        
    var div = document.createElement("div");
    div.className="image";    
    div.setAttribute("onclick",onClick);
    var div1 = document.createElement("img");
    div1.src = "Images/"+ path + ".png";
    div.appendChild(div1);
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