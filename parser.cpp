 #include <string.h>
 #include <stdio.h>
 #include <ctype.h>
 
 int htoi(unsigned char *s) 
{ 
    int i;
    int n = 0; 
    if (s[0] == '0' && (s[1]=='x' || s[1]=='X')) //Determine whether there is a leading 0x or 0X
    { 
        i = 2; 
    } 
    else 
    { 
        i = 0; 
    } 
    for (; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >='A' && s[i] <= 'Z');++i) 
    {   
        if (tolower(s[i]) > '9') 
        { 
        n = 16 * n + (10 + tolower(s[i]) - 'a'); 
        } 
        else 
        { 
            n = 16 * n + (tolower(s[i]) - '0'); 
        } 
    } 
    return n; 
} 

int _find_key(unsigned char *data,int data_length,unsigned char *key,int key_length,int *position)
{
    int i = *position;
    if(key == NULL || i<0)
    {
        return 0;
    }
    for(; i <= data_length-key_length; i++)
    {
        if( memcmp(data+i, key, key_length) == 0 )
        {
            *position = i;
            return 1;
        }
    }
    return 0;
}

int de_chunked(unsigned char *data,int data_length,unsigned char *dest,int *dest_length)
{
    char       chunked_hex[CHUNKED_MAX_LEN + 1];    //  Hexadecimal block length
    int        chunked_len;                        //  Block length
    int        ret;
    int        begin = 0;
    int        end = 0;
    int        i = 0;
    int        index = 0;

    ret = _find_key(data, data_length, " 0\r\n\r\n", 5, &end);
    if (ret == 0)    //Incomplete information
        return 0;

    ret = _find_key(data, data_length, "\r\n\r\n", 4, &begin);
    begin = begin + 4;    //Move to the beginning of the data

    while(memcmp(data+begin,"0\r\n\r\n",5) != 0)
    {
        //Get the current block length
        ret = _find_key(data+begin,CHUNKED_MAX_LEN,"\r\n",2,&i);
        if (ret == 0)    //Incomplete information
           return 0;
        memcpy(chunked_hex,data+begin,i);
        chunked_hex[i] = '\0';
        chunked_len = htoi(chunked_hex);
//Move to the current block data segment
        begin = begin + i + 2;
//Get current block data
        if (memcmp(data+begin+chunked_len,"\r\n",2) != 0)
            return 0;    //The information is wrong
        memcpy(dest+index,data+begin,chunked_len);
        index = index + chunked_len;
//Move to the next block length
        begin = begin + chunked_len + 2;
        i = begin;
        if(begin > end)    //Structural error
            return -1;
    }
    *dest_length = index;
    return 1;
}