#include<iostream>
#include <stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/stat.h>
#include<strings.h>
#include<errno.h>
#include<unistd.h>
#include <fcntl.h> 
#include<arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<bits/stdc++.h>
using namespace std;

map<string,string> map_client_file;
map<string,string> map_file_filepath;
map<string,string> map_username_pass;



//map<string,vector<string>> client_basic_details;

int main(int argc, char *argv[])
{
    char buffer[512*1024];
    int buffer_size=512*1024;

    string server_ip_port=argv[1];
    string ip_server;
    string port_server;
    char ch=':';
    int i=0;
    //while(s[i] != ':')
    while(server_ip_port[i] != ch)
    {
        ip_server=ip_server+server_ip_port[i];
        //cout<<endl;
        ++i;
    }
    ip_server[i+1]='\0';
    ++i;


   // cout<<endl<<strlen(argv[1])<<endl;

    while(i < server_ip_port.size() )
    {
        port_server=port_server+server_ip_port[i];
        ++i;
    }
    port_server[i+1]='\0';
   // cout<<"ip_server"<<ip_server<<endl;
    //cout<<"port_server"<<port_server<<endl;
    cout<<"tracker started"<<endl;

    int socket_id=socket(AF_INET, SOCK_STREAM, 0);
    if(socket_id<0)
    cout<<"Error in connection"<<endl;

        cout<<"socket id:"<<socket_id<<endl;



    struct sockaddr_in serveraddr,clientaddr;
    bzero((char *) &serveraddr, sizeof(serveraddr));

     
    serveraddr.sin_family=AF_INET;
    int port=atoi(port_server.c_str());
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    //cout<<"port:"<<endl<<port<<endl;


    int bind_return=bind(socket_id,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    if(bind_return<0)
    {
        cout<<"Error in Binding"<<endl;
        exit(1);
    }
    cout<<"bind_return:"<<bind_return<<endl;
    int listen_status=listen(socket_id,100);
    if(listen_status<0)
    {
        cout<<"ERROR IN LISTEN"<<endl;
        exit(1);
    }
cout<<"listen status:"<<listen_status<<endl;
    int clientlen=sizeof(clientaddr);

    while(1)
    {
    int new_sock=accept(socket_id, (struct sockaddr *) &clientaddr, (socklen_t*)&clientlen);
        if(new_sock<=0)
            {
                 cout<<"ERROR IN CONNECTING CLIENT"<<endl;
                 exit(1);
            }

    int command_length;
    int recv_status=recv(new_sock,&command_length,sizeof(command_length),0);
    if(recv_status<0)
        {
        cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
        exit(0);
        }
    cout<<"command_length:"<<command_length<<endl;

    char command[command_length+1];
    command[command_length]='\0';
    recv_status=recv(new_sock,command,sizeof(command)-1,0);
    if(recv_status<0)
    {
        cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
        exit(0);
    }
    cout<<"command:"<<command<<endl;
    string com=command;

     string upload_file="upload_file";
     string download_file="download_file";
     string create_user="create_user";
     string login="login";
     
     
     
     
     
     if(strcmp(upload_file.c_str(),com.c_str())==0)
     {
         
//UPLOAD FILE





       //code for UPLOAD FILE  
         
        int file_path_size;
        int recv_status=recv(new_sock,&file_path_size,sizeof(file_path_size),0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
         
         
        printf("\n %d\n",file_path_size);

        
        char file_path[file_path_size+1];
        file_path[file_path_size]='\0';
        recv_status=recv(new_sock,file_path,sizeof(file_path)-1,0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
        printf("\n %s\n",file_path);

        string file_p=file_path;
        int len=file_path_size;
        cout<<endl<<len;
        int index;
        for(int i=len-1;i>=0;i--)
        {
            if(file_p[i]=='/')
            {
                index=i;
                break;
            }
        }
        string file_name=file_p.substr(index+1,(len-(index+1)));
        cout<<"file name is"<<file_name<<endl;

        map_file_filepath[file_name]=file_p;


        






        int port_number;
        recv_status=recv(new_sock,&port_number,sizeof(port_number),0);
        if(recv_status<0)
        {
                cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
                exit(0);
        }
        cout<<"port_number:"<<port_number<<endl;

        int upload_status;
        if(recv_status>0)
         upload_status=1;
         else 
         upload_status=0;

        
        
       // string filename=file_name;
        string port_of_client=to_string(port_number);
        if(map_client_file.count(file_name))
        {
            string temp=map_client_file[file_name];
            temp.append(" ");
            temp.append(port_of_client);
            map_client_file[file_name]=temp;
            cout<<map_client_file[file_name]<<endl;
            cout<<map_file_filepath[file_name]<<endl;
        }
        else
        {
            map_client_file[file_name]=port_of_client;
            cout<<map_client_file[file_name]<<endl;
            cout<<map_file_filepath[file_name]<<endl;
        }
        
    
        
        
        int send_status=send(new_sock,&upload_status,sizeof(upload_status),0);
        if(send_status<0)
        {
            cout<<endl<<"error in sending"<<endl;
        }




         
         
         
         cout<<"string matched";
     }
     else if(strcmp(download_file.c_str(),com.c_str())==0)
     {

            //code for download

        int file_name_length;
        int recv_status=recv(new_sock,&file_name_length,sizeof(file_name_length),0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }



        char file_name[file_name_length+1];
        file_name[file_name_length]='\0';
        recv_status=recv(new_sock,file_name,sizeof(file_name)-1,0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }

        string filename=file_name;
        string filepath=map_file_filepath[filename];
        int len=filepath.size();

        int send_status=send(new_sock,&len,sizeof(len),0);
        if(send_status<0)
        {
            cout<<endl<<"error in sending"<<endl;
        }

        char filepathtosend[len];
        strcpy(filepathtosend,filepath.c_str());


        send_status=send(new_sock,&filepathtosend,sizeof(filepathtosend),0);
        if(send_status<0)
        {
                    cout<<"error while send status";
                        exit(0);
        }

        string portdetails=map_client_file[filename];
        int portdetailslen=portdetails.size();
        char portstring[portdetailslen];
        strcpy(portstring,portdetails.c_str());



         send_status=send(new_sock,&portdetailslen,sizeof(portdetailslen),0);
        if(send_status<0)
        {
            cout<<endl<<"error in sending"<<endl;
        }


        send_status=send(new_sock,&portstring,sizeof(portstring),0);
        if(send_status<0)
        {
                    cout<<"error while send status";
                        exit(0);
        }
        







     }
     else if(strcmp(create_user.c_str(),com.c_str())==0)
     {
         //CODE FOR CREATE USER
         int count=0;
         int recv_status;
         int username_len;
         recv_status=recv(new_sock,&username_len,sizeof(username_len),0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
        else ++count;
         
         
       // printf("\n %d\n",username_len);

        
        char username[username_len+1];
        username[username_len]='\0';
        recv_status=recv(new_sock,username,sizeof(username)-1,0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
        else ++count;
        printf("%s\n",username);

        //
            int password_len;
         recv_status=recv(new_sock,&password_len,sizeof(password_len),0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
        else ++count;
         
         
       // printf("\n %d\n",password_len);

        
        char password[password_len+1];
        password[password_len]='\0';
        recv_status=recv(new_sock,password,sizeof(password)-1,0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
        else ++count;
        printf("%s\n",password);

            int send_status;
            send_status=send(new_sock,&count,sizeof(count),0);
            if(send_status<0)
            {
                    cout<<"error while send status";
                        exit(0);
            }

            string user=username;
            string ps=password;
            map_username_pass[user]=ps;
            cout<<"entries added are :"<<user<<"::"<<map_username_pass[user]<<endl;

        //


     }
     else if(strcmp(login.c_str(),com.c_str())==0)
     {
         //CODE FOR LOGIN

         int count=0;
         int recv_status;
         int username_len;
         recv_status=recv(new_sock,&username_len,sizeof(username_len),0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
        else ++count;
         
         
        //printf("\n %d\n",username_len);

        
        char username[username_len+1];
        username[username_len]='\0';
        recv_status=recv(new_sock,username,sizeof(username)-1,0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
        else ++count;
        //printf("\n %s\n",username);

        //
            int password_len;
         recv_status=recv(new_sock,&password_len,sizeof(password_len),0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
        else ++count;
         
         
       // printf("\n %d\n",password_len);

        
        char password[password_len+1];
        password[password_len]='\0';
        recv_status=recv(new_sock,password,sizeof(password)-1,0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
        else ++count;
        //printf("\n %s\n",password);

            int send_status;
            

            string user=username;
            string ps=password;
            if(map_username_pass.count(user))
            {
                string temp=map_username_pass[user];
                if(strcmp(ps.c_str(),temp.c_str())==0)
                {
                    send_status=send(new_sock,&count,sizeof(count),0);
                    if(send_status<0)
                    {
                            cout<<"error while send status";
                                exit(0);
                    }
                }
                else
                {
                    count=0;
                    send_status=send(new_sock,&count,sizeof(count),0);
                    if(send_status<0)
                    {
                            cout<<"error while send status";
                                exit(0);
                    }
                }
                          
            }
            //map_username_pass[user]=ps;
            //cout<<"entries added are :"<<user<<"::"<<map_username_pass[user]<<endl;

        
     }
     else cout<<"Not matching with any command:"<<endl;
//     //{

    }
    
    
    
    


    
    
    
    
    
    
    
    
    


    
    
    
    
    
    



    //}
    //else
    //cout<<"string comparisionfailed"<<endl;







}