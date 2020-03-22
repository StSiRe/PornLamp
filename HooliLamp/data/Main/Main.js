function MainPage()   {
    ClearElements();
    var main = document.getElementById("main");
    var fragment = document.createDocumentFragment();
    main.appendChild(CreateForm(CreateImage("logo")));
    main.appendChild(Separator());
    main.appendChild(CreateWrapper(
        CreateFormLeft(CreateButtonImage("Animations","Animations()")),
        CreateFormRight(CreateImage("Music"))
    ));  
    main.appendChild(Separator());
    main.appendChild(CreateWrapper(
        CreateFormLeft(CreateImage("Alarm")),
        CreateFormRight(CreateImage("Settings"))
     ));   
}