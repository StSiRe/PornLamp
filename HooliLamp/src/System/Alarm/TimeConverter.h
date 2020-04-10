int ConvertDayToInt(String day)
{
    if(day == "Sunday")
        return 0;
    else if(day=="Monday")
        return 1;
    else if(day=="Tuesday")
        return 2;
    else if(day=="Wednesday")
        return 3;
    else if(day=="Thursday")
        return 4;
    else if(day=="Friday")
        return 5;
    else if(day == "Saturday")
        return 6;
    else if(day == "All")
        return 7;
    else
        return -1;    
}
String ConvertIntToDay(int day)
{
    if(day == -1)
        return "";
    else if(day == 0)
        return "Sunday";
    else if(day == 1)
        return "Monday";
    else if(day == 2)
        return "Tuesday";
    else if(day == 3)
        return "Wednesday";
    else if(day == 4)
        return "Thursday";
    else if(day == 5)
        return "Friday";
    else if(day == 6)
        return "Saturday";
    else
        return "All";        
}