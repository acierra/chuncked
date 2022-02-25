#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
 
 int htoi(unsigned char *s) 
{ 
    int i;
    int n = 0; 
    if (s[0] == '0' && (s[1]=='x' || s[1]=='X')) 
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

int find_key(std::string *data,int data_length,unsigned char *key,int key_length,int *position)
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

int de_chunked(std::string *data, int data_length)
{
    int        chunked_len;                        
    int        ret;
    int        begin = 0;
    int        end = 0;
    int        i = 0;
    int        index = 0;

    ret = find_key(data, data_length, " 0\r\n\r\n", 5, &end);
    if (ret == 0)    
        return 0;

    ret = _find_key(data, data_length, "\r\n\r\n", 4, &begin);
    begin = begin + 4;  

    while(memcmp(data+begin,"0\r\n\r\n",5) != 0)
    {

        ret = find_key(data+begin, data_lenght, "\r\n",2,&i);
        if (ret == 0)
           return 0;
        
        
    return 1;
}



std::string chuncked(std::string str)
{
    int len;

    len = str.length();
    de_chuncked(&str, len);
    return (str);
}

int main()
{
    std::string http_chunk_header = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nchunk 2\r\n0\r\n";
    chunked(http_chunk_header);
    std::cout << http_chunk_header;
    return (0);
}
