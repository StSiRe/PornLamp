struct AlarmClock
{
    std::vector<String> Days;
    int Hour;
    int Minute;
    bool Enabled = false;
    int Repeat = 0;
    String Music;
};