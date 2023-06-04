#include <stdio.h>
 int in_len = 0, new_len = 0, old_len = 0, add_len = 0, add_time = 0, index_out = 0;
int strlen_my(const char *str)
{
    int count = 0;
    while (*str != '\0')
    {
        str++;
        count++;
    }
    return count;
}
const char *findStr(const char *in, const char *oldstr ,int outlen)
{
    while (*in != '\0'&& (add_time + 1) * add_len + in_len <= outlen - 1)
    {
        if (*in == *oldstr)
        {
            int i = 0, j = 0;
            while (*(in + i) != '\0' && *(oldstr + j) != '\0' && *(in + i) == *(oldstr + j))
            {
                i++;
                j++;
            }
            if (*(oldstr + j) == '\0')
            {
                return in;
            }
        }
        in++;
    }
    return in;
}
int str_replace(const char *in, char *out, int outlen, const char *oldstr, const char *newstr)
{
   
    const char *tmp;
    // 得到原字符串长度，替换字符长度，被替换字符串长度，两者之差
    in_len = strlen_my(in);
    new_len = strlen_my(newstr);
    old_len = strlen_my(oldstr);
    add_len = new_len - old_len; // 可以为负数
    tmp = in;

    // 寻找字串
    while (*in != '\0')
    {
        in = findStr(in, oldstr,outlen);
        if (*in != '\0' && (add_time + 1) * add_len + in_len <= outlen - 1)
        {
            for (; tmp <= in - 1; tmp++, index_out++)
            {
                *(out + index_out) = *tmp;
            }
            in = in + old_len;
            tmp = in;
            // 对out替换
            for (int i = 0; i < new_len; i++, index_out++)
            {
                *(out + index_out) = *(newstr + i);
            }
            add_time++;
        }
        else
        {
            *(out + index_out) = *(in);
            index_out++, in++;
        }
    }
    *(out+index_out) = '\0';
    return add_time;
}

// 执行替换函数
//  void replace(const char *in, char *out,const char )
int main(int argc, char const *argv[])
{
    char str[] = "aaabbbccc";
    char out[100] = "";
    char newstr[] = "379789";
    char oldstr[] = "bbb";
    printf("%d\n",str_replace(str, out, 14, oldstr, newstr));
    printf("%s\n",out);
    return 0;
}
