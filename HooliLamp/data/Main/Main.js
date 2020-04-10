function MainPage()   {
    ClearElements();
    var main = document.getElementById("main");
    var fragment = document.createDocumentFragment();
    main.appendChild(CreateForm(CreateImage("logo")));
    main.appendChild(Separator());
    main.appendChild(CreateWrapper(
        CreateFormLeft(CreateButtonImage("Animations","CreateAnimationWindow()")),
        CreateFormRight(CreateImage("Music"))
    ));  
    main.appendChild(Separator());
    main.appendChild(CreateWrapper(
        CreateFormLeft(CreateButtonImage("Alarm","CreateAlarmWindow()")),
        CreateFormRight(CreateImage("Settings"))
     ));   
}