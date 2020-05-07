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
    LoadAlarmData();
}
//Сохранить все будильники
function SaveAlarmData()
{
    var text = JSON.stringify(alarms);
    var xhr = new XMLHttpRequest();

    xhr.open('GET', '/Alarm/SaveAll?'+ "SaveAll" + '=' + text, false);

    xhr.send();
}
//Сохранить один определенный будильник
function SaveAlarmData(id)
{
    var data = alarms[id]; 
    data.id = id;   
    var text = JSON.stringify(data);
    var xhr = new XMLHttpRequest();

    xhr.open('GET', '/Alarm/Save?'+ "Save" + '=' + text, false);

    xhr.send();
}
function SaveButtonClick(id)
{
    var div = document.getElementById("AlarmForm:" + id);
    SaveAlarmData(id);
    if(div == undefined || div == null) return;

    //-----Чистим предыдущие элементы
    var counter = div.childNodes.length;
    for(var i=counter -1;i>= 0;i--){
        div.removeChild(div.childNodes[i]);
    }
    //---Изменяем класс и размер окна
    div.className = "alarm";
    var days = alarms[id].Days;//Дни недели
    var rDays = "";
    if(days[1] == 1) rDays+= "Пн,";    
    if(days[2] == 1) rDays+= "Вт,";    
    if(days[3] == 1) rDays+= "Ср,";    
    if(days[4] == 1) rDays+= "Чт,";    
    if(days[5] == 1) rDays+= "Пт,";    
    if(days[6] == 1) rDays+= "Сб,";    
    if(days[0] == 1) rDays+= "Вс";
    var hour = alarms[id].Hour;
    var minute = alarms[id].Minute;
    var state = alarms[id].Enabled;
    div.appendChild(CreateAlarmClock(hour + ":" + minute));
    div.appendChild(CreateAlarmDays(rDays));
    div.appendChild(CreateAlarmSettingsImage("MiniSettings","AlarmSettingsClick("+ id +")"));
    var button = document.createElement("div");
    button.classList.add("alarmToogleButton");
    button.appendChild(CreateToogleButton("Alarm:" + id +"Button","StateButtonClick("+ id +")",state));
    div.appendChild(button);

}
function DeleteButtonClick(id)
{
    //В случае если выбранный будильник надо удалить
    alarms[id] = null;
    var div = document.getElementById("AlarmForm:"+id);
    var xhr = new XMLHttpRequest();

    xhr.open('GET', '/Alarm/Delete?'+ "Delete" + '=' + id, false);

    xhr.send();
    if(div == undefined || div == null) return;
    div.remove();
}

//TimePicker Code
function ArrowUpClick(id,type)
{
    if(type)
    {
        var div = document.getElementById("HourPicker:"+ id+ ":Hour");
        var time = Number(div.innerText);
        if(time < 23) time++;
        else time = 0;
        div.innerText = time;    
        alarms[id].Hour = time; 
    }
    else
    {
        var div = document.getElementById("MinutePicker:"+ id+ ":Minute");
        var time = Number(div.innerText);
        if(time < 59) time++;
        else time = 0;
        div.innerText = time;    
        
        alarms[id].Minute = time;
    }
}
//TimePicker Code
function ArrowDownClick(id,type)
{
    if(type)
    {
        var div = document.getElementById("HourPicker:"+ id+ ":Hour");
        var time = Number(div.innerText);
        if(time > 0) time--;
        else time = 23;
        div.innerText = time; 
        alarms[id].Hour = time;   
    }
    else
    {
        var div = document.getElementById("MinutePicker:"+ id+ ":Minute");
        var time = Number(div.innerText);
        if(time > 0) time--;
        else time = 59;
        div.innerText = time;    
        alarms[id].Minute = time;
    }
}

let DayOfWeek = ["Пн","Вт","Ср","Чт","Пт","Сб","Вс"];
function CreateDaysPicker(id,current)
{
    var div = document.createElement("div");
    div.classList.add("dayPicker");
    var text = document.createElement("div");
    text.innerText = "Выберите дни:";
    text.classList.add("dayPicker_instruction");
    div.appendChild(text);
    div.appendChild(Separator());  
    var div1 = document.createElement("div");
    div1.classList.add("dayPicker_box");
    for(var i=0;i<7;i++)
    {
        var box = document.createElement("div");
        if(current[i] == 0)
            box.classList.add("dayPicker_day"); 
        else                   
            box.classList.add("dayPicker_day_clicked"); 
        box.id = "DayPicker_day:"+id+":" + i;
        box.setAttribute("onclick","DayPicker_dayClick("+id+","+i+")");
        var element = document.createElement("text");
        element.classList.add("dayPicker_text");
        element.innerText = DayOfWeek[i];
        box.appendChild(element);
        div1.appendChild(box);
    }
    div.appendChild(div1);
    return div;
}
function DayPicker_dayClick(id,i)
{
    var div = document.getElementById("DayPicker_day:"+id+":" + i);
    if(div.className == "dayPicker_day")
    {
        alarms[id].Days[i] = 1;
        div.className = "dayPicker_day_clicked";
    }
    else
    {        
        alarms[id].Days[i] = 0;
        div.className = "dayPicker_day";
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
function CreateTimePicker(id,hour_t,minute_t)
{
    var div = document.createElement("div");
    div.classList.add("timePicker");

    var box = document.createElement("div");
    var hour = document.createElement("span");
    hour.classList.add("timePicker_Hour");
    hour.innerText = hour_t;
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
    min.innerText = minute_t;
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
    var div = document.getElementById("main");
    div.appendChild(Separator());
    var id = alarms.length;
    div.appendChild(CreateAlarm("0","0",true,alarms.length));
    var newArr = new Array(id+1);
    for(var i=0;i<id;i++)
    newArr[i] = alarms[i];
    alarms = newArr;
    //Work when in array has min one element
    alarms[id] = alarms[id - 1];
    alarms[id].Hour = 0;
    alarms[id].Minute =0;
    alarms[id].Days = [0,0,0,0,0,0,0];
    alarms[id].Enabled = true;
    AlarmSettingsClick(id);
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
    div.appendChild(CreateTimePicker(id,alarms[id].Hour,alarms[id].Minute));
    div.appendChild(Separator());
    div.appendChild(CreateDaysPicker(id,alarms[id].Days));
    div.appendChild(CreateAlarmSaveButton(id));
}
function ParseDaysToLogic(day)
{
    var result = [0,0,0,0,0,0,0];
    for(var i=0;i< day.length;i++)
    {
        if(day[i] == 0)
            result[6] = 1;
        else if(day[i] == 1)
            result[0] = 1;
        else if(day[i] == 2)
            result[1] = 1;
        else if(day[i] == 3)
            result[2] = 1;
        else if(day[i] == 4)
            result[3] = 1;
        else if(day[i] == 5)
            result[4] = 1;
        else if(day[i] == 6)
            result[5] = 1;
        else if(day[i] == "All")
            result = [1,1,1,1,1,1,1];
    }
    return result;
}
function StateButtonClick(id)
{  
    var button = document.getElementById("Alarm:" + id +"Button");
    alarms[id].Enabled = button.control.checked;
    SaveAlarmData(id);
}
function CreateAlarm(time,days,enabled,id)
{
    var div = CreateAlarmForm("AlarmForm:"+ id);
    div.appendChild(CreateAlarmClock(time));
    div.appendChild(CreateAlarmDays(days));
    div.appendChild(CreateAlarmSettingsImage("MiniSettings","AlarmSettingsClick("+ id +")"));
    var button = document.createElement("div");
    button.classList.add("alarmToogleButton");
    button.appendChild(CreateToogleButton("Alarm:" + id +"Button","StateButtonClick("+ id +")",enabled));
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
function ParseDays(day)
{
    var result = "";
    for(var i=0;i< day.length;i++)
    {
        if(day[i] == 0)
            result+="Вс";
        else if(day[i] == 1)
            result+= "Пн";
        else if(day[i] == 2)
            result+= "Вт";
        else if(day[i] == 3)
            result+= "Ср";
        else if(day[i] == 4)
            result+= "Чт";
        else if(day[i] == 5)
            result+= "Пт";
        else if(day[i] == 6)
            result+= "Сб";
    }


    var res1 = "";
    for(var i = 0;i < result.length;i++)
    {
        if(i!=0)
            if(i%2 == 0)
                res1+= ",";
        res1 +=result[i];
    }
    return res1;
}
function LoadAlarmData()
{
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (this.status == 200) {
            var data = JSON.parse(this.responseText);
            alarms = data.Alarms;

            var doc = document.getElementById("main");
            for(var i =0;i< alarms.length;i++)
            {                
                var days = alarms[i].Days;//Дни недели
                var hour = alarms[i].Hour;
                var minute = alarms[i].Minute;
                var state = alarms[i].Enabled;
                var repeat = alarms[i].Repeat;
                var SunriseTime = alarms[i].Sunrise;
                var music = alarms[i].Music;
                
                doc.appendChild(Separator());
                doc.appendChild(CreateAlarm(hour + ":" + minute,ParseDays(days),state,i));
                alarms[i].Days = ParseDaysToLogic(days);
            }
        }
    };
    xhr.open('GET', '/Alarm/Data', false);
    xhr.send();
}