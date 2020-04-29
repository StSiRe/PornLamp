var alarms;

function CreateAlarmWindow()
{
    ClearElements();
    var main = document.getElementById("main");
    main.appendChild(CreateForm(
        CreateBackButton(),
        CreateImage("Alarm")
    ));
    main.appendChild(Separator());
    main.appendChild(CreateNewAlarmBlock()); 
    main.appendChild(Separator());
    main.appendChild(CreateTestAlarm()); 
    main.appendChild(Separator());
    main.appendChild(CreateTestAlarm());
    LoadAlarmData();
}
function SaveAlarmData()
{

}
function DeleteButtonClick(id)
{
    //В случае если выбранный будильник надо удалить
}
function ArrowUpClick(id,type)
{
    if(type)
    {
        var div = document.getElementById("HourPicker:"+ id+ ":Hour");
        var time = Number(div.innerText);
        if(time < 23) time++;
        else time = 0;
        div.innerText = time;    
    }
    else
    {
        var div = document.getElementById("MinutePicker:"+ id+ ":Minute");
        var time = Number(div.innerText);
        if(time < 59) time++;
        else time = 0;
        div.innerText = time;    
    }
}
function ArrowDownClick(id,type)
{
    if(type)
    {
        var div = document.getElementById("HourPicker:"+ id+ ":Hour");
        var time = Number(div.innerText);
        if(time > 0) time--;
        else time = 23;
        div.innerText = time;    
    }
    else
    {
        var div = document.getElementById("MinutePicker:"+ id+ ":Minute");
        var time = Number(div.innerText);
        if(time > 0) time--;
        else time = 59;
        div.innerText = time;    
    }
}





function CreateNewAlarmBlock()
{
    return CreateForm(AddClass("alarmNewButton",CreateButtonImage("Plus","CreateNewAlarm()")));
}
function CreateAlarmSaveButton(id)
{
    var div = document.createElement("div");
    div.setAttribute("onclick","SaveButtonClick("+ id +")");
    div.classList.add("alarmSaveButton");
    div.appendChild(CreateImage("Save"));
    return div;
}
function CreateTimePicker(id)
{
    var div = document.createElement("div");
    div.classList.add("timePicker");

    var box = document.createElement("div");
    var hour = document.createElement("span");
    hour.classList.add("timePicker_Hour");
    hour.innerText = "00";
    hour.id = "HourPicker:"+ id+ ":Hour";
    var arrowUp = document.createElement("img");
    arrowUp.src = "https://image.flaticon.com/icons/svg/2089/2089643.svg";
    arrowUp.classList.add("timePicker_Arrow");
    arrowUp.setAttribute("onclick","ArrowUpClick("+ id +","+ true +")");
    arrowUp.id = "ArrowUp:" + id + ":Hour";
    var arrowDown = document.createElement("img");
    arrowDown.src = "https://image.flaticon.com/icons/svg/2089/2089636.svg";
    arrowDown.classList.add("timePicker_Arrow");
    arrowDown.setAttribute("onclick","ArrowDownClick("+ id +","+ true +")");
    arrowDown.id = "ArrowDown:" + id + ":Hour";
    box.appendChild(arrowUp);
    box.appendChild(hour);
    box.appendChild(arrowDown);
    box.classList.add("timePicker_Col");
    div.appendChild(box);

    var col = document.createElement("div");
    col.classList.add("timePicker_Col");
    col.innerText=":";

    div.appendChild(col);

    var box1 = document.createElement("div");    
    box1.classList.add("timePicker_Col");

    var min = document.createElement("span");
    min.classList.add("timePicker_Minute");
    min.innerText = "00";
    min.id = "MinutePicker:"+ id+ ":Minute";
    var arrowUp1 = document.createElement("img");
    arrowUp1.src = "https://image.flaticon.com/icons/svg/2089/2089643.svg";
    arrowUp1.classList.add("timePicker_Arrow");
    arrowUp1.setAttribute("onclick","ArrowUpClick("+ id +","+ false +")");
    arrowUp1.id = "ArrowUp:" + id + ":Minute";
    var arrowDown1 = document.createElement("img");
    arrowDown1.src = "https://image.flaticon.com/icons/svg/2089/2089636.svg";
    arrowDown1.classList.add("timePicker_Arrow");
    arrowDown1.setAttribute("onclick","ArrowDownClick("+ id +","+ false +")");
    arrowDown1.id = "ArrowDown:" + id + ":Minute";
    box1.appendChild(arrowUp1);
    box1.appendChild(min);
    box1.appendChild(arrowDown1);
    div.appendChild(box1);

    return div;
}
function CreateNewAlarm()
{
    alert("ХУнйя");
}
function AlarmSettingsClick(id)
{
    //alert("Settings");
    //var alarm = alarms[id];
    var div = document.getElementById("AlarmForm:"+id);
    if(div == undefined || div == null) return;

    //-----Чистим предыдущие элементы
    var counter = div.childNodes.length;
    for(var i=counter -1;i>= 0;i--){
        div.removeChild(div.childNodes[i]);
    }
    //---Изменяем класс и размер окна
    div.className = "alarmSelected";

    //---Начинаем добавлять элементы
    div.appendChild(CreateAlarmDeleteButton(id));
    div.appendChild(CreateTimePicker(id));
    div.appendChild(CreateAlarmSaveButton(id));
}
function StateButtonClick(id)
{  
    var button = document.getElementById("Alarm:" + id +"Button");
    alarms[id].Enabled = button.control.checked;
    SendAlarmData();
}
function CreateAlarm(time,days,enabled,id)
{
    var div = CreateAlarmForm("AlarmForm:"+ id);
    div.appendChild(CreateAlarmClock(time));
    div.appendChild(CreateAlarmDays(days));
    div.appendChild(CreateAlarmSettingsImage("MiniSettings","AlarmSettingsClick("+ id +")"));
    var button = document.createElement("div");
    button.classList.add("alarmToogleButton");
    button.appendChild(CreateToogleButton(id+"Button","StateButtonClick("+ id +")",enabled));
    div.appendChild(button);

    return div;
}
function CreateAlarmDeleteButton(id)
{
    var div = document.createElement("div");
    div.classList.add("alarmDeleteButton");        
    div.setAttribute("onclick","DeleteButtonClick("+ id +")");
    div.appendChild(CreateImage("Delete"));
    return div;
}
function CreateAlarmClock(clock)
{
    var time = document.createElement("text");
    time.classList.add("alarmTime");
    time.innerText=clock;
    return time;
}
function CreateAlarmDays(days)
{
    var div = document.createElement("text");
    div.classList.add("alarmDays");
    div.innerText = days;
    return div;
}
function CreateAlarmSettingsImage(path,onClickHandler)  {
    if(path == null){
        return null;
    }        
    var div1 = document.createElement("img");    
    div1.setAttribute("onclick",onClickHandler);
    div1.classList.add("alarmEditButton");  
    div1.src = "Images/"+ path + ".svg";
    return div1;
}
function CreateTestAlarm()
{
    var div = CreateAlarm("12.55","1234",true,1);
    return div;
}
function LoadAlarmData()
{
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (this.status == 200) {
            var data = JSON.parse(this.responseText);
            alarms = data.Alarms;

            var doc = document.getElementById("main");
            for(var i =0;i< alarms,length;i++)
            {                
                var days = alarms[i].Days;//Дни недели
                var hour = alarms[i].Hour;
                var minute = alarms[i].Minute;
                var state = alarms[i].Enabled;
                var repeat = alarms[i].Repeat;
                var SunriseTime = alarms[i].Sunrise;
                var music = alarms[i].Music;
                doc.appendChild(CreateAlarm(hour + ":" + minute,days,state,"Alarm:"+i));
            }

        }
    };
    xhr.open('GET', '/Alarm/Data', false);
    xhr.send();
}