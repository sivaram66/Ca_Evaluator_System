#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct CARecord {
    char name[100];
    int id;
    char code[20];
    float ca_marks;
};
struct CARecord r1;
void create_record();
void search_record();
void modify_record();
void delete_record();
void display_record();


int main() {
    int choice;
    
    do {
        printf("\n");
        printf("CA Evaluator System\n");
        printf("-------------------\n");
        printf("1. Create Record\n");
        printf("2. Search Record\n");
        printf("3. Modify Record\n");
        printf("4. Delete Record\n");
        printf("5. Display Records\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_record();
                break;
            case 2:
                search_record();
                break;
            case 3:
                modify_record();
                break;
            case 4:
                delete_record();
                break;
            case 5:
                display_record();
                break;
            case 6:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}

void create_record() {
    printf("\nEnter Name:");
    scanf("%s", r1.name);
    printf("Enter ID:");
    scanf("%d", &r1.id);
    printf("Course Code:");
    scanf("%s", r1.code);
    printf("Enter CA Marks:");
    scanf("%f", &r1.ca_marks);

    FILE *fp = fopen("records.txt", "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fwrite(&r1, sizeof(r1), 1, fp);
    fclose(fp);

    printf("Record created successfully.\n");
}

void search_record() {
    int id, found = 0;
    printf("ID : ");
    scanf("%d", &id);

    FILE *fp = fopen("records.txt", "r");
    while (fread(&r1, sizeof(r1), 1, fp)) {
        if (r1.id == id) {
            printf("\n Record found: \n");
            printf("Name: %s\n", r1.name);
            printf("ID: %d\n", r1.id);
            printf("Course Code: %s\n", r1.code);
            printf("CA Marks: %.2f\n", r1.ca_marks);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found) {
        printf("\n Couldn't find record.\n");
    }
}

void modify_record() {
    int id, found = 0;

    printf("\nEnter ID to modify:");
    scanf("%d", &id);

    FILE *fp = fopen("records.txt", "r");
    FILE *temp_fp = fopen("tempCa.txt", "w");

    while (fread(&r1, sizeof(r1), 1, fp)) {
        if (r1.id == id)
		 {
            printf("\nEnter new details:\n");
            printf("Name: ");
            scanf("%s", r1.name);
            printf("ID: ");
            scanf("%d", &r1.id);
            printf("Course Code: ");
            scanf("%s", r1.code);
            printf("CA Marks: ");
            scanf("%f", &r1.ca_marks);

            if (temp_fp == NULL)
			{
                printf("Error opening file.\n");
                return;
            }
            fwrite(&r1, sizeof(r1), 1, temp_fp);
            fclose(fp);
            fclose(temp_fp);
            printf("Record has been modified.\n");
            found = 1;
        }
		else 
		{
            fwrite(&r1, sizeof(r1), 1, temp_fp);
        }
    }

    if (!found) {
        printf("\n Record not found.\n");
    } else {
        remove("records.txt");
        rename("tempCa.txt", "records.txt");
    }
}

void delete_record(){
    int id,found=0;

    printf("\n Enter ID to delete: ");
    scanf("%d",&id);
    FILE *fp=fopen("records.txt","r");
    FILE *f=fopen("tempCa.txt","w");
    while(fread(&r1,sizeof(r1),1,fp))
	{
        if (r1.id!=id)
		{
			fwrite(&r1,sizeof(r1),1,f);
        }
        else
        {
        	found =1;
		}
    }
    fclose(fp);
	fclose(f);

    if(!found){
        printf("\n Record not found.\n");
    }
    else
    {
    	remove("records.txt");
    	rename("tempCa.txt","records.txt");
    	printf("Record Deleted Sucessfully");
	}
}

void display_record(){
    FILE *fp = fopen("records.txt","r");
    if(fp==NULL){
        printf("Error opening file.\n");
        return;
    }

    printf("\n All Records:\n");
    printf("---------\n");
	while(fread(&r1,sizeof(r1),1,fp))
	{
		    printf("Name: %s\n",r1.name);
            printf("ID: %d\n",r1.id);
            printf("Course code: %s\n",r1.code);
            printf("CA MARKS: %.2f\n\n",r1.ca_marks);
	}
    fclose(fp);
}

