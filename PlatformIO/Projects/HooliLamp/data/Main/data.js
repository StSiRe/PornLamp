
function Animations()
{
    var main = document.getElementById("main");
    var fragment = document.createDocumentFragment();
    var element = CreateForm(CreateButton());
    fragment.appendChild(element);
    fragment.appendChild(CreateForm(CreateImage("logo")));
    element1 = CreateForm(CreateImage("logo").innerHTML+ CreateButton().innerHTML);
    fragment.appendChild(element1);
    main.appendChild(fragment);
}
function CreateButton()
{
    var div = document.createElement("label");
    div.className = "switch";
    var div1 = document.createElement("input");
    div1.type = "checkbox";
    var div2 = document.createElement("span");
    div2.className = "slider round";
    div1.appendChild(div2);
    div.appendChild(div1);
    /*
    <label class="switch">
            <input type="checkbox">
            <span class="slider round"></span>
          </label>
    */
    return div;
}
function CreateForm(innerHTML)
{
    var div = document.createElement("div");
    div.innerHTML = "<div class='form'>"+
                    innerHTML.innerHTML+
                    "</div>";
    return div;
}
function CreateImage(path)
{
    var div = document.createElement("div");
    div.innerHTML = "<div class = 'image'>" +
                    "<img src = 'Images/"+path+".png'>"
                    "</div>";
    return div;
}