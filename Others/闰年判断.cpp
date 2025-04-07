// 没啥可读性版 :)
bool LeapYear(int year)
{
    return year % 4 == 0 && (year % 400 == 0 || !(year % 400 !=0 && year % 100 == 0));
}