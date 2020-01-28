//include files
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <bitset>
#include <limits>
using namespace std;

//global variables
int ip[4]={-1};
int n;
int subnet_custom[4] = {0};  //decimal for custom subnet
int subnet_default[4] = {0};
int network_addr[4]={0};
int ipClass;
int b_bits=0;
int bits_net_addr[32]={0};
int bits_i_subnet[32] ={0};
int broadcast_addr[4] = {0};
int final_addr[4]={0};
int is_cidr=0;


/*------Data for case 3-----------------*/
int no_hosts= 0;
int no_subnets = 0;
int no_hosts_bits =0,no_subnets_bits =0;
int custom_subnet_bits_case3[32] ={0};

/*----------------variables for growth-----------------*/
int f=0,f2,f3; //flag shows that once I have taken successfully inputs at start
int temp_no_subnets=0,temp_no_hosts=0;
/*------------------- utiltiy functions -----------------------------*/
//get ip input will be needed in each case
void get_ip_input()
{
  s:
  int c=0,f=0;
  string ip_input;
  cout<<"Enter ip address :";
  getline(cin,ip_input);
  stringstream ss(ip_input);
  int i;
  int j=0;
  while(ss>>i)
  {
    c++;
    ip[j]=i;
    j++;
    if(ss.peek()=='.')ss.ignore();
  }
  for(int i=0;i<4;i++)
    {
      if(ip[i]<0||ip[i]>255)f=1;
    }
    if(c==4)
      {
        if(f==1){cout<<endl<<"octets are not in range\n";goto s;}
      }
    else {cout<<"YOU MUSt provide 4 octest\n";goto s;}


}
void get_class()
{
  cout<<"--------------------------------------------------------->\n";
  if (ip[0] == 10) {
		//return 1;	// Class A Private address blocks //
    cout << "IP Class: Private block, Class 'A' " << endl;
    ipClass = 1;
	}else if (ip[0] == 172 && ip[1] >= 16 && ip[1] <= 31) {
		//return 2;	// Class B Private address blocks //
    cout << "IP Class: Private block, Class 'B'" << endl;
    ipClass = 2;
	}else if (ip[0] == 192 && ip[1] == 168) {
		//return 3;	// Class C Private address blocks //
    cout << "IP Class: Private block, Class 'C'" << endl;
    ipClass = 3;
	}else if (ip[0] == 127) {
		//return 4;	// Loopback Address Reserved address blocks //
    cout << "IP Class: Reserved block, System Loopback Address" << endl;
    ipClass = 1;
	}else if (ip[0] >= 0 && ip[0] < 127) {
		//return 5;
    cout << "IP Class: A" << endl;
    ipClass = 1;
	}else if (ip[0] > 127 && ip[0] < 192) {
		//return 6;
    cout << "IP Class: B" << endl;
    ipClass = 2;
	}else if (ip[0] > 191 && ip[0] < 224) {
		//return 7;
    cout << "IP Class: C" << endl;
    ipClass = 3;
	}else if (ip[0] > 223 && ip[0] < 240) {
		//return 8;
    cout << "IP Class: D" << endl;
    ipClass = 4;
    cout << "!! This is a reserved Class D Multicast IP Address Block" << endl;
	}else if (ip[0] > 239 && ip[0] <= 255) {
		//return 9;
    cout << "IP Class: E" << endl;
    ipClass = 5;
    cout << "!! This is a reserved Class E Multicast IP Address Block" << endl;

	}else{
    cout << "Not in Range" << endl;
		//return 0;	// Out of Range //
	}
}

//for case 3
void get_input_host_subnet()
{
  cout<<"Enter the no of required hosts :";
  cin>>no_hosts;
  cout<<"Enter the no of required subnets :";
  cin>>no_subnets;
  cout<<endl;

  /*--newly added--*/
  //calculate no_hosts_bits And no_subnets_bits
  no_hosts_bits = (int)ceil(log2 ((double)no_hosts));
  //cout<<"no of bits in host part is :"<<no_hosts_bits<<endl;
  if(no_hosts_bits>(32-ipClass*8)||no_hosts_bits<=0){
    cout<<"Invalid no. of host:::innput again\n";
    get_input_host_subnet();
  }
  no_subnets_bits = (int)ceil(log2 ((double)no_subnets));
  //cout<<"according to class and no. of hosts possible value of  no. of bits in subnet part is :"<<32-(ipClass*8+no_hosts_bits)<<endl;
  //checking is needed bits are possible or not
  if(ipClass!=4&&(no_hosts_bits+no_subnets_bits)>((4-ipClass)*8))
  {
    //we have 24 bits
    cout<<"no available enough bits for no. of host and no. of subnets:: Change inputs"<<endl;
    get_input_host_subnet();
    //if(f==0){exit(-1);}
    //else if(f==1){
      //function is called from growth
     //ask again from user what he wants
     //f2==0;
    //}
  }
  else if(ipClass==4){
    cout<<"no subnetting possible in class D\n";
    exit(0);
  }
  //else if(f==1)f2=1;
  /*---------------*/
}
//compute no of bits required for subnetting in host and subnet part
void compute_host_subnet_bits()
{
  //calculate no_hosts_bits And no_subnets_bits
  no_hosts_bits = (int)ceil(log2 ((double)no_hosts));
  cout<<"no of bits in host part is :"<<no_hosts_bits<<endl;
  if(no_hosts_bits>(32-ipClass*8)||no_hosts_bits<=0){
    cout<<"Invalid no. of host\n";
    exit(-1);
  }
  no_subnets_bits = (int)ceil(log2 ((double)no_subnets));
  cout<<"according to class and no. of hosts possible value of  no. of bits in subnet part is :"<<32-(ipClass*8+no_hosts_bits)<<endl;
  //checking is needed bits are possible or not
  if(ipClass!=4&&(no_hosts_bits+no_subnets_bits)>((4-ipClass)*8))
  {
    //we have 24 bits
    cout<<"no available enough bits for no. of host and no. of subnets:: Change inputs"<<endl;
    if(f==0){exit(-1);}
    else if(f==1){
      //function is called from growth
     //ask again from user what he wants
     f2==0;
    }
  }
  else if(ipClass==4){
    cout<<"no subnetting possible in class D\n";
    exit(0);
  }
  else if(f==1)f2=1;
}

//get custom subnet in case 1
void get_custom_subnet_case1()
{
  for(int i=31;i>=0;i--)
    {
      if((i>=32-no_hosts_bits))
      custom_subnet_bits_case3[i] = 0;
      else custom_subnet_bits_case3[i] = 1;
      //cout<<custom_subnet_bits_case3[i]<<"\t";
    }
    //updating value of n,b_bits,
    n=32-no_hosts_bits;
    if(ipClass==4)b_bits=0;
    else{
      b_bits=((4-ipClass)*8)-no_hosts_bits;
    }
    // cout<<"CIDR format n value is :"<<n<<endl;
    // cout<<"b_bits will be :"<<b_bits<<endl;
    //cout<<endl;

}
//input cidr bits in case 2
void get_cidr_input_case2()
{
  cout<<"enter custom subnet in CIDR format :";
  cin>>n;
  if(ipClass==4&&n<32){
    cout<<"Invalid CIDR value :: supernetworking in under development \n";
    exit(-1);

  }
  else if(n<(ipClass*8)||n>31){
    cout<<"Invalid CIDR value \n";
    exit(-1);
  }
}

//take input custom subnet in decimal format for case 3
void get_input_custom_subnet_in_decimal_case3()
{
  cout<<"still to be implemented\n";
}
//calculate decimal format custom subnet
void get_decimal_custom_subnet()
{
  int n1=n;
  int i=0;
  while(n>8)
    {
      n=n-8;
      subnet_custom[i] = 255;i++;
    }
  if(n!=0)
    {
      int sum = 0,c=7;
      while(n>0)
        {
          sum+=pow(2,c);
          c--;
          n--;
        }
      subnet_custom[i] =sum;
    }
    cout<<"--------------------------------------------------------->\n";
  cout<<"\nCustom subnet mask is \t";
  for(int i=0;i<4;i++)
  {
    if(i<3)cout<<subnet_custom[i]<<".";
    else if(i==3)cout<<subnet_custom[i]<<endl;
  }
  n=n1;
}

void print_default_subnet()
{
  if(ipClass==1)
    {
      subnet_default[0]=255;
      subnet_default[1]=0;
      subnet_default[2]=0;
      subnet_default[3]=0;
    }
  else if(ipClass==2)
    {
      subnet_default[0]=255;
      subnet_default[1]=255;
      subnet_default[2]=0;
      subnet_default[3]=0;

    }
  else if(ipClass==3)
    {
      subnet_default[0]=255;
      subnet_default[1]=255;
      subnet_default[2]=255;
      subnet_default[3]=0;
    }
  else if(ipClass==4||ipClass==5)
    {
      subnet_default[0]=subnet_custom[0];
      subnet_default[1]=subnet_custom[1];
      subnet_default[2]=subnet_custom[2];
      subnet_default[3]=subnet_custom[3];
    }

  cout<<"Default subnet mask is: \t";
  for(int i=0;i<4;i++)
    {
      if(i<3)
      cout<<subnet_default[i]<<".";
      else if(i==3)cout<<subnet_default[i]<<endl;
    }
    cout<<"--------------------------------------------------------->\n";
}


void get_network_address()
{

  cout<<"network address is \t";
  for(int i=0;i<4;i++)
    {
      network_addr[i] = ip[i]&subnet_custom[i];
      if(i<3){
        cout<<network_addr[i]<<".";

      }
      else if(i=3){
        cout<<network_addr[i]<<"\n";
      }
    }
}

void get_number()
{
  cout<<"no of subnets is "<<(int)pow(2,b_bits)<<endl;
  if(ipClass==1){
  cout<<"no of address unique is "<<(int)pow(2,24-b_bits)<<endl;
  cout<<"no of address usable is "<<(int)pow(2,24-b_bits)-2;}
  else if(ipClass==2){
  cout<<"no of address unique is "<<(int)pow(2,16-b_bits)<<endl;
  cout<<"no of address usable is "<<(int)pow(2,16-b_bits)-2;}
  else if(ipClass==3){
  cout<<"no of address unique is "<<(int)pow(2,8-b_bits)<<endl;
  cout<<"no of address usable is "<<(int)pow(2,8-b_bits)-2;}
  cout<<endl;


}

void get_broadcast_address()
{
  //getting 8 bits of each octets of netework address
  //int b[8] = {0}; //for temporary store
  for(int i=0;i<4;i++)
    {
      bitset<8> b(network_addr[i]);
      //cout<<"for "<<i<<"th octets of network_addr bits are"<<endl;
      for(int j=7;j>=0;j--)
        {
          bits_net_addr[(i*8)+(7-j)] = b[j];
          //cout<<b[j];
        }
        //cout<<endl<<endl;
    }
    for(int i=n;i<32;i++)bits_net_addr[i]=1;
    //cout<<"bits of broadcast address is "<<endl;
    //for(int i=0;i<32;i++){
      //cout<<bits_net_addr[i]<<"\t";
      //if((i+1)%8==0)cout<<endl;
    //}
    //cout<<endl;
    int b[8]={0};
    for(int i=0;i<4;i++)
      {
        for(int j=0;j<8;j++)
          {
            b[j] = bits_net_addr[j+(i*8)];
          }
         int sum = 0;
         for(int k=7;k>=0;k--)
          {
            if(b[k]==1)
            sum+=(int)pow(2,7-k);
          }
          //cout<<sum<<endl;
          broadcast_addr[i]=sum;
      }
      cout<<"broadcast address for given ip's network is\t";
      for(int i=0;i<4;i++)
        {
          if(i<3)cout<<broadcast_addr[i]<<".";
          else if(i==3)cout<<broadcast_addr[i]<<endl;
        }



}
void Initial_and_final(int range)
{
  if(range>(int)pow(2,b_bits)||range<=0){
    cout<<"this subnet is not possible as per given data\n";
    exit(-1);
  }
  //copy bits_net_addr into bits_i_subnet array
  for(int i=0;i<32;i++)bits_i_subnet[i] = bits_net_addr[i];

  //for calculation of ith subnet
  int bits_temporary_subnet_nUmber[b_bits] = {0};
  int mayank[b_bits]={0};
  int x = range-1;
  int k=0;
  while(1)
    {
      mayank[k] =x%2;
      x=x/2;
      //cout<<"x is"<<x<<endl;
      //cout<<"bk is "<<b[k]<<endl;
      if(x==1){mayank[k+1]=1;break;}
      else if(x==0){mayank[k+1]=0;break;}
      else k++;
    }
  //in reverse order copy subnet bits into temporary array
  for(int i= b_bits-1;i>=0;i--)
    {
      bits_temporary_subnet_nUmber[b_bits-i-1]=mayank[i];
      //cout<<mayank[i];
    }
    //cout<<endl;

    //printing bit position
    //cout<<"\n  start from "<<ipClass*8;
    //cout<<"\n end "<<ipClass*8+b_bits<<endl;
  //insert subnet number into network address
  for(int i = ipClass*8,j=0;(i<(ipClass*8+b_bits))&&(j<b_bits);i++,j++)
  {
    bits_i_subnet[i] = bits_temporary_subnet_nUmber[j];
    //cout<<bits_temporary_subnet_nUmber[j]<<"\t";
  }
  cout<<endl<<endl;
  //printing final ip address of that subnett
  //for(int i=0;i<32;i++)
    //{
      //if((i+1)%8!=0)cout<<bits_i_subnet[i]<<"\t";
      //else cout<<bits_i_subnet[i]<<endl;
    //}
    bits_i_subnet[31] = 1;
    int b[8]={0};
    for(int i=0;i<4;i++)
      {
        for(int j=0;j<8;j++)
          {
            b[j] = bits_i_subnet[j+(i*8)];
          }
         int sum = 0;
         for(int k=7;k>=0;k--)
          {
            if(b[k]==1)
            sum+=(int)pow(2,7-k);
          }
          //cout<<sum<<endl;
          final_addr[i]=sum;
      }

      cout<<"final address for given subnet's is : ";
      for(int i=0;i<4;i++)
        {
          if(i<3)cout<<final_addr[i]<<".";
          else if(i==3)cout<<final_addr[i]<<endl;
        }


        //for Initial address
          for(int i=n;i<31;i++)
            {
              bits_i_subnet[i]=0;
            }
          bits_i_subnet[31]=0;


          for(int i=0;i<4;i++)
            {
              for(int j=0;j<8;j++)
                {
                  b[j] = bits_i_subnet[j+(i*8)];
                }
               int sum = 0;
               for(int k=7;k>=0;k--)
                {
                  if(b[k]==1)
                  sum+=(int)pow(2,7-k);
                }
                //cout<<sum<<endl;
                final_addr[i]=sum;
            }

            cout<<"Initial address for given subnet's is : ";
            for(int i=0;i<4;i++)
              {
                if(i<3)cout<<final_addr[i]<<".";
                else if(i==3)cout<<final_addr[i]<<endl;
              }



}


void get_borrow_bits()
{
  double param;int b;
  if(ipClass==1)
  {
    //class A
    if(subnet_custom[1]==255)
      {
        if(subnet_custom[2]==255)
        {
          if(subnet_custom[3]==255)
            {
              b_bits = 24;
            }
          else{
            param = 255-subnet_custom[3];
            b_bits = 8-ceil(log2(param));
            b_bits+=16;
          }
        }
        else
        {
          param = 255-subnet_custom[2];
          b_bits = 8-ceil(log2(param));
          b_bits+=8;
        }
      }
    else
      {
        param = 255-subnet_custom[1];
        b_bits = 8-ceil(log2(param));
      }
  }
  else if(ipClass==2)
    {
      //class B
      //Initial 2 octets will be 255
      if(subnet_custom[2]==255)
        {
          if(subnet_custom[3]==255)
            {
              b_bits=16;
            }
          else{
            param = 255-subnet_custom[3];
            b_bits = 8-ceil(log2(param));
            b_bits+=8;
          }
        }
      else
      {
        param = 255-subnet_custom[2];
        b_bits = 8-ceil(log2(param));

      }
    }

  else if(ipClass==3)
    {
      if(subnet_custom[3]==255)b_bits=8;
      else{
        param = 255-subnet_custom[3];
        b_bits = 8-ceil(log2(param));
      }
    }
  else if(ipClass>3){cout<<"no subnettting "; b_bits=0;}
  cout<<"borrowed bits for subnetting is   = "<<b_bits<<endl;
}


//compute growth whe
//when users gives growth in subnets
void growth_in_subnets()
{
  float subnets_growth=0;
  cout<<"Enter percentage growth in subnets :";
  cin>>subnets_growth;
  temp_no_subnets=no_subnets;
  no_subnets = (int)pow(2,b_bits);
  no_subnets= no_subnets+((no_subnets*subnets_growth)/100);
  //calculate no_hosts_bits And no_subnets_bits
  int required_bits = (int)ceil(log2 ((double)no_subnets));
  cout<<"no of bits in subnet part after growth is :"<<required_bits<<endl;
  if(required_bits<b_bits&&is_cidr==0){
    cout<<"previous scheme will be enough for this growth\n";
  }
  else if(required_bits>b_bits&&is_cidr==0){
    cout<<"Warning::::not possible\n";
    no_subnets=temp_no_subnets;
  }
  else if(is_cidr==1){
    if((required_bits-b_bits)<(32-ipClass*8-b_bits)){
      cout<<"for such growth "<<required_bits-b_bits<<" are taken from host part\n";
      n=n+(required_bits-b_bits);
      b_bits = required_bits;
      cout<<"subnet part bits are :"<<required_bits;
      get_decimal_custom_subnet();
      get_network_address();
      get_number();
      get_broadcast_address();
      cout<<"--------------------------------------------------------->\n";
    }
    else{
      cout<<"growth is not possible\n";
      no_subnets=temp_no_subnets;
    }
  }

}

//when users gives growth in subnets
void growth_in_hosts()
{
  if(is_cidr==1){
    cout<<"we can not provide growth in host part if we are taking CIDR subnets\n";
    f3=0;
    return ;
  }
  int host_growth=0;
  cout<<"Enter percentage growth in hosts :";
  cin>>host_growth;
  temp_no_hosts=no_hosts;
   no_hosts= no_hosts+((no_hosts*host_growth)/100);
  f=1;
  compute_host_subnet_bits();
  if(f2==1)
  {
    //cout<<"growth is possible here so changed other parameters are :\n";
    get_custom_subnet_case1();
    get_decimal_custom_subnet();
    f3=1;
  }
  else if(f2==0){
    no_hosts = temp_no_hosts;
    f3=0;}

}

//perform future growth
void perform_future_growth()
{
  start:
  int choice;
  cout<<"#Growth in 1.subnets 2.hosts \n";
  cout<<"Enter your choice :";
  cin>>choice;
  switch (choice) {
    case 1:growth_in_subnets();
          break;

    case 2:growth_in_hosts();break;
    default:cout<<"Invalid input\n";goto start;
  }

}


/*-------------------------------main function -----------------------*/

int main()
{
  start:
  cout<<"-------------------------IP Calculator-------------------------------\n";
  cout<<"OPTIONS :: What you want to give as input :\n";
  cout<<"\n(1) ip address  & no of host & no of subnets\n(2) ip address & CIDR format n bits\n";
  int  rply;
  cout<<"\nEnter your choice:";
  cin>>rply;
  cin.ignore (numeric_limits<streamsize>::max(), '\n'); //discard characters until newline is found
  cout<<"\n";
  if(rply<4)get_ip_input();else{cout<<"Invalid input\n";exit(-1);}
 if((ip[0]==0&&ip[1]==0&&ip[2]==0&&ip[3]==0)||(ip[0]==255&&ip[1]==255&&ip[2]==255&&ip[3]==255)){
    cout<<"Not valid ip\n";
    exit(-1);
  }
  get_class();
  print_default_subnet();

  if(ip[0]==127){

    exit(-1);
  }
  switch (rply) {
    case 1:f=0;
            get_input_host_subnet();
            compute_host_subnet_bits();
            get_custom_subnet_case1();
            get_decimal_custom_subnet();
            break;
    case 2:
            is_cidr=1;
            get_cidr_input_case2();
            get_decimal_custom_subnet();
            get_borrow_bits();
            break;
    default: cout<<"Invalid input\n";exit(-1);break;
  }
  label1:
  get_network_address();
  get_number();
  get_broadcast_address();
  cout<<"--------------------------------------------------------->\n";

  if(b_bits<=0){
    cout<<"to print any subnet range provide b_bits greater than 0\n";
    goto label2;
  }
  cout<<"#Options \n1. In case you want to print a specified subnet's range (for first subnet enter 1 and so on)\n2. In case you want to print all subnets range\n3. In case you dont want to print subnet range\n";
  int c;
  cout<<"Enter your choice :";
  cin>>c;
  if(c==1){
    int range;
    cout<<"Enter nth subnet of which you want to find range -->";
    cin>>range;
    Initial_and_final(range);
  }
  else if(c==2){
    int x = (int)pow(2,b_bits);
    //cout<<"hoo\n"<<x<<endl;
    for(int i=1;i<=x;i++){
      cout<<"\t\t ******"<<i<<"th subnets range *******";
      Initial_and_final(i);
      cout<<endl;
    }
  }
  else if(c==3){}
  label2:
  cout<<"--------------------------------------------------------->\n";
  while(1){
  //ending:
    cout<<"#Option :\n1. if you want to exit\n2. if you want to give future growth\n3. if want to reset everything\nEnter your choice:";
    int c;
    cin>>c;
    if(c==1){
      exit(0);
    }
    else if(c==2){
      //under development
      perform_future_growth();
      if(f3==0)continue;
      else if(f3==1)goto label1;
    }
    else if(c==3){
      goto start;
    }
  }
}
