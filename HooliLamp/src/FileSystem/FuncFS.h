void SetValue(String value,String &result,String wrong)
{
    if(value != NULL && value != "" && value != "null")
    {
        result = value;
    }
    else
    {        
        result = wrong;
    }
}
void SetValue(int value,int &result,int wrong)
{
    if(value != NULL)
    {
        result = value;
    }
    else
    {        
        result = wrong;
    }
}
void SetValue(bool value,bool &result,bool wrong)
{
    if(value != NULL)
    {
        result = value;
    }
    else
    {        
        result = wrong;
    }
}