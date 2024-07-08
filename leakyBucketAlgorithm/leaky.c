#include<stdio.h>

int main(){
    int incoming_packet_size;
    int outgoing_rate;
    int bucket_capacity;
    int number_of_inputs;
    int current_storage =  0;
    
    printf("Enter bucket size : ");
    scanf("%d", &bucket_capacity);
    printf("Enter outgoing rate : ");
    scanf("%d", &outgoing_rate);
    printf("Enter number of inputs : ");
    scanf("%d", &number_of_inputs);

    while(number_of_inputs != 0){
        printf("Enter incoming packet size : ");
        scanf("%d", &incoming_packet_size);
        int available_space = bucket_capacity - current_storage;
        if(incoming_packet_size <= available_space){
            current_storage += incoming_packet_size;
            printf("Added packet. Current level : %d/%d\n", current_storage, bucket_capacity);   
        }else{
            int packets_dropped = incoming_packet_size - available_space ;
            printf(" Dropped %d packets.\n", packets_dropped);
            current_storage = bucket_capacity;
            printf("Current level after dropping : %d/%d\n", current_storage, bucket_capacity);
        }

        current_storage -= outgoing_rate;
        if(current_storage < 0){
            current_storage = 0;
        }
        printf("After outgoing, %d packets left in buffer out of %d\n\n", current_storage, bucket_capacity);
        number_of_inputs--;
    }
}

/*
output
------
sj@lenovo:~/leakyBucketAlgorithm$ gcc leakybucket.c -o leakybucket
sj@lenovo:~/leakyBucketAlgorithm$ ./leakybucket
Enter bucket size : 100
Enter outgoing rate : 30
Enter number of inputs : 4
Enter incoming packet size : 50
Added packet. Current level : 50/100
After outgoing, 20 packets left in buffer out of 100

Enter incoming packet size : 80
Added packet. Current level : 100/100
After outgoing, 70 packets left in buffer out of 100

Enter incoming packet size : 60
 Dropped 30 packets.
Current level after dropping : 100/100
After outgoing, 70 packets left in buffer out of 100

Enter incoming packet size : 20
Added packet. Current level : 90/100
After outgoing, 60 packets left in buffer out of 100

sj@lenovo:~/leakyBucketAlgorithm$ 
*/
