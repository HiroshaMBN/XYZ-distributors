#include <stdio.h>
#include <mysql/mysql.h>

MYSQL *conn = NULL;
MYSQL_RES *res = NULL;
MYSQL_ROW row = NULL;
char *hostname = "localhost";
char *username = "root";
char *password = "g*71$";
char *database_name = "test_app";

char item_name[200];
int qty;
double unit_price;
double total_price;

int database_administration()
{
    int choice;
    conn = mysql_init(NULL);
    printf("please enter your choice\n\n");
    printf(" [1] Item section\n");
    printf(" [2] Vehicles section\n");
    printf(" [3] Supplier section\n");
    printf(" [4] Reporting section\n");
    scanf("%d", &choice);
    if (!(mysql_real_connect(conn, hostname, username, password, database_name, 0, NULL, 0) == NULL))
    {
        if (choice == 1)
        {
            int choice_item;

            printf("**Item section**\n Please select your choice\n");
            printf(" [1] Add Item\n");
            printf(" [2] Search Item\n");
            printf(" [3] Edit Item\n");
            printf(" [4] Delete Item\n");
            scanf("%d", &choice_item);
            if (choice_item == 1)
            {

                printf("Enter item name: ");
                scanf("%s", item_name);
                printf("Enter quantity: ");
                scanf("%d", &qty);
                printf("Enter unit price: ");
                scanf("%lf", &unit_price);

                // Loop until a valid quantity is entered
                while (1)
                {
                    printf("Enter quantity: ");
                    if (scanf("%d", &qty) != 1)
                    {
                        printf("Please enter a valid number.\n");
                        // Clear input buffer
                        while (getchar() != '\n')
                            ;
                    }
                    else
                    {
                        break;
                    }
                }

                while (1)
                {
                    printf("Enter unit price: ");
                    if (scanf("%lf", &unit_price) != 1)
                    {
                        printf("Please enter a valid number.\n");
                        // Clear input buffer
                        while (getchar() != '\n')
                            ;
                    }
                    else
                    {
                        break;
                    }
                }

                total_price = qty * unit_price;

                // Constructing SQL query string with user input values
                char query[256];
                // fgets(item_name, sizeof(item_name), stdin);
                sprintf(query, "INSERT INTO item (item_name, qty, unit_price, total_price) VALUES ('%s', '%d', '%lf', '%lf')", item_name, qty, unit_price, total_price);

                // Executing SQL query
                if (mysql_query(conn, query) != 0)
                {
                    printf("Item save failed..\n");
                    fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
                }
                else
                {
                    printf("Item saved successfully..\n");
                }
            }
            else if (choice_item == 2)
            {
                int search_method;
                char item_name;
                char item_id;
                char query[256];
                sprintf(query, "SELECT * FROM item ");

                printf(" [1] Item search by name\n");
                printf(" [2] Item search by id\n");
                scanf("%d", &search_method);

                if (search_method == 1)
                {
                    printf("Please enter item name: ");
                    scanf("%s", &item_name);
                    sprintf(query, "SELECT * FROM `item` WHERE item_name like '%%soft%%'");

                    // Execute the query
                    if (mysql_query(conn, query))
                    {
                        fprintf(stderr, "%s\n", mysql_error(conn));
                        // exit(1);
                    }

                    // Store the result
                    res = mysql_store_result(conn);

                    // Get the number of fields
                    int num_fields = mysql_num_fields(res);

                    // Fetch and print column headers
                    MYSQL_FIELD *fields = mysql_fetch_fields(res);
                    for (int i = 0; i < num_fields; i++)
                    {
                        printf("%s ", fields[i].name);
                    }
                    printf("\n");

                    // Fetch and print the result rows
                    while ((row = mysql_fetch_row(res)))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf("%s ", row[i] ? row[i] : "NULL");
                        }
                        printf("\n");
                    }
                }
                else if (search_method == 2)
                {
                    printf("Please enter item ID\n");
                    scanf("%s", item_id);
                    // printf(item_id);
                }
                else
                {
                    printf("Please enter valid input\n");
                }
            }
            else if (choice_item == 3)
            {
            }
            else if (choice_item == 4)
            {
            }
        }
        else if (choice == 2)
        {
            printf("**Vehicles section**\n");
        }
        else if (choice == 3)
        {
            printf("**Supplier section**\n");
        }
        else if (choice == 4)
        {
            printf("**Reporting section**\n");
        }
        else
        {
            printf("Please enter valid input values.\n e.g 1,2,3, or 4\n");
        }
    }
}

int main()
{

    conn = mysql_init(NULL);
    int selection;
    printf("!!!!!!!!!!!!!! ***** Welcome to XYZ Distributors ***** !!!!!!!!!!!!!!\n");
    printf("\n");
    printf("Please Enter your choice as number\n\n");
    printf(" [1] Check database connectivity\n");
    printf(" [2] Go to other activity section\n");

    scanf("%d", &selection);

    if (selection == 1)
    {
        printf("you are now interacted in database connection test section\n");

        // mysql connection
        if (conn == NULL)
        {
            fprintf(stderr, "mysql_init() failed\n");
            return 1;
        }

        if (mysql_real_connect(conn, hostname, username, password, database_name, 0, NULL, 0) == NULL)
        {
            fprintf(stderr, "mysql_real_connect() failed\n");
            mysql_close(conn);
            return 1;
        }
        else
        {
            printf("Database connection successfully..!\n");
        }
    }
    else if (selection == 2)
    {
        // DBA handling class
        database_administration();
    }
    else
    {

        printf("Please enter valid input values.\n e.g 1 or 2\n");
    }

    // database_administration();
    /*

    if (mysql_query(conn, "SELECT * FROM your_table")) {
        fprintf(stderr, "mysql_query() failed\n");
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    printf("ID\tName\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\t%s\n", row[0], row[1]);
    }

    mysql_free_result(res);
    mysql_close(conn);
*/
    return 0;
}
