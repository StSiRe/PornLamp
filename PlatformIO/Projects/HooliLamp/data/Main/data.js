
function Animations()
{
    var main = document.getElementById("main");
    var fragment = document.createDocumentFragment()
    fragment.appendChild(CreateButton());
    main.appendChild(fragment);
}
function CreateButton()
{
    var div = document.createElement("div");
    div.innerHTML = "<div class='Button>" +" dfkdfk"+
                    "</div>";
    return div;
}