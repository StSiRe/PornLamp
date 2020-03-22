function CreateAlarmWindow()
{
    ClearElements();
    var main = document.getElementById("main");
    main.appendChild(CreateForm(
        CreateBackButton(),
        CreateImage("Alarm")
    ));
    main.appendChild(CreateForm);
}
function LoadAlarmData()
{

}