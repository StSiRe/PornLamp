<<<<<<< HEAD

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
    
=======
function LoadData()
{
    let data = fetch("/settings");
    var json = JSON.parse(data);
>>>>>>> 480e674851add6205d717fbfe2def178fd43f1c4
}
function SendParameter(param)
{
    
}