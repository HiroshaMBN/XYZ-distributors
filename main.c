#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
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

int available_suppliers()
{
    char query[256];
    printf("******************Available Suppliers and items****************** \n ");

    snprintf(query, sizeof(query), "SELECT * FROM `suppliers` ");

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
        printf("%-12s| ", fields[i].name);
    }
    printf("\n");

    // Fetch and print the result rows
    while ((row = mysql_fetch_row(res)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            printf("%-12s| ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
}

int available_items()
{
    char query[256];
    printf("******************Available Suppliers and items****************** \n ");

    snprintf(query, sizeof(query), "SELECT * FROM `item` ");

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
        printf("%-12s| ", fields[i].name);
    }
    printf("\n");

    // Fetch and print the result rows
    while ((row = mysql_fetch_row(res)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            printf("%-12s| ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
}
int DBA()
{
    int choice;
    conn = mysql_init(NULL);
    char query[256];
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
            int sup_id;

            printf("**Item section**\n Please select your choice\n");
            printf(" [1] Add Item\n");
            printf(" [2] Search Item\n");
            printf(" [3] Edit Item\n");
            printf(" [4] Delete Item\n");
            scanf("%d", &choice_item);
            if (choice_item == 1)
            {
                // show available suppliers
                available_suppliers();

                char query[256];

                char sup_id[50]; // Assuming the supplier ID won't exceed 49 characters
                printf("Please enter supplier id from supplier table: ");
                scanf("%49s", sup_id); // Limit input to 49 characters to avoid buffer overflow

                snprintf(query, sizeof(query), "SELECT COUNT(*) FROM suppliers WHERE id = '%s'", sup_id);

                if (mysql_query(conn, query))
                {
                    fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
                    // return;
                }

                MYSQL_RES *result = mysql_store_result(conn);
                if (!result)
                {
                    fprintf(stderr, "Failed to store result: %s\n", mysql_error(conn));
                    // return;
                }

                MYSQL_ROW row = mysql_fetch_row(result);
                if (!row)
                {
                    fprintf(stderr, "Failed to fetch row: %s\n", mysql_error(conn));
                    mysql_free_result(result);
                    // return;
                }

                // Check if the count is greater than 0
                int count = atoi(row[0]);
                mysql_free_result(result);
                if (count > 0)
                {
                    // // Execute the query
                    // if (mysql_query(conn, query))
                    // {
                    //     fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
                    //     // return -1;
                    // }

                    // printf("Enter item name: ");
                    // scanf("%s", item_name);

                    // // Loop until a valid quantity is entered
                    // while (1)
                    // {
                    //     printf("Enter quantity: ");
                    //     if (scanf("%d", &qty) != 1)
                    //     {
                    //         printf("Please enter a valid number.\n");
                    //         // Clear input buffer
                    //         while (getchar() != '\n')
                    //             ;
                    //     }
                    //     else
                    //     {
                    //         break;
                    //     }
                    // }

                    // while (1)
                    // {
                    //     printf("Enter unit price: ");
                    //     if (scanf("%lf", &unit_price) != 1)
                    //     {
                    //         printf("Please enter a valid number.\n");
                    //         // Clear input buffer
                    //         while (getchar() != '\n')
                    //             ;
                    //     }
                    //     else
                    //     {
                    //         break;
                    //     }
                    // }

                    // // Constructing SQL query string with user input values
                    // char query[256];
                    // fgets(item_name, sizeof(item_name), stdin);
                    // sprintf(query, "INSERT INTO item (item_name, qty, unit_price) VALUES ('%s', '%d', '%lf')", item_name, qty, unit_price);
                    sprintf(query, "INSERT INTO item (supplier_id) VALUES ('%s')", sup_id);

                    // // Executing SQL query
                    if (mysql_query(conn, query) != 0)
                    {
                        printf("Item save failed..\n");
                        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
                    }
                    else
                    {
                        printf("Item saved successfully..\n");
                    }

                    // printf("Item saved successfully..\n");
                }
                else
                {
                    printf("WARNING!!\nSupplier id is not matching with our records.\nPlease check suppliers and try again..!\n");
                }
            }
            else if (choice_item == 2)
            {
                int search_method;

                char item_id[100];
                char query[256];
                char item_name[100];
                sprintf(query, "SELECT * FROM item ");

                printf(" [1] Item search by name\n");
                printf(" [2] Item search by id\n");
                printf(" [3] Show all items\n");
                scanf("%d", &search_method);

                if (search_method == 1)
                {
                    printf("Please enter item name: ");
                    scanf("%99s", item_name); // Limit input to prevent buffer overflow
                    snprintf(query, sizeof(query), "SELECT * FROM `item` WHERE item_name LIKE '%%%s%%'", item_name);

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
                        printf("%-12s| ", fields[i].name);
                    }
                    printf("\n");

                    // Fetch and print the result rows
                    while ((row = mysql_fetch_row(res)))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf("%-12s| ", row[i] ? row[i] : "NULL");
                        }
                        printf("\n");
                    }
                }
                // search
                else if (search_method == 2)
                {
                    printf("Please enter item ID\n");
                    scanf("%99s", item_id); // Limit input to prevent buffer overflow
                    snprintf(query, sizeof(query), "SELECT * FROM `item` WHERE id LIKE '%%%s%%'", item_id);

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
                        printf("%-12s| ", fields[i].name);
                    }
                    printf("\n");

                    // Fetch and print the result rows
                    while ((row = mysql_fetch_row(res)))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf("%-12s| ", row[i] ? row[i] : "NULL");
                        }
                        printf("\n");
                    }
                }
                else if (search_method == 3)
                {
                    snprintf(query, sizeof(query), "SELECT * FROM `item` ");

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
                        printf("%-12s| ", fields[i].name);
                    }
                    printf("\n");

                    // Fetch and print the result rows
                    while ((row = mysql_fetch_row(res)))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf("%-12s| ", row[i] ? row[i] : "NULL");
                        }
                        printf("\n");
                    }
                }
                else
                {
                    printf("Please enter valid input\n");
                }
            }
            else if (choice_item == 3)
            {
                char query[256];
                int id;
                char item_name[100]; // Adjust size as needed
                int qty;
                double unit_price;
                double total_price;
                // Prompt user for item id to update
                printf("Please enter item id: ");
                scanf("%d", &id);

                // Prompt user for new values
                printf("Please enter new item name: ");
                scanf("%99s", item_name); // Limit input to prevent buffer overflow

                printf("Please enter new quantity: ");
                scanf("%d", &qty);

                printf("Please enter new unit price: ");
                scanf("%lf", &unit_price);

                // Calculate total_price
                total_price = qty * unit_price;

                // Format the update query
                snprintf(query, sizeof(query),
                         "UPDATE `item` SET item_name='%s', qty=%d, unit_price=%.2f WHERE id=%d",
                         item_name, qty, unit_price, id);

                // Execute the query
                if (mysql_query(conn, query))
                {
                    fprintf(stderr, "Update query failed: %s\n", mysql_error(conn));
                }
                else
                {
                    printf("Record updated successfully.\n");
                }
            }
            else if (choice_item == 4)
            {
                int id;
                char query[256];
                printf("Please enter id of item\n");
                scanf("%d", &id);
                snprintf(query, sizeof(query), "Delete from `item` where id ='%d'", id);
                // Execute the query
                if (mysql_query(conn, query))
                {
                    fprintf(stderr, "Delete query failed: %s\n", mysql_error(conn));
                }
                else
                {
                    printf("Record delete successfully.\n");
                }
            }
        }
        else if (choice == 2)
        {
            int choice_vehicles;
            printf("**Vehicles section**\n Please select your choice\n");
            printf(" [1] Add vehicle\n");
            printf(" [2] Search vehicle\n");
            printf(" [3] Edit vehicle\n");
            printf(" [4] Delete vehicle\n");
            printf(" [5] Items load to vehicle\n");
            printf(" [6] Items unload to vehicle\n");
            scanf("%d", &choice_vehicles);
            // add vehicle
            if (choice_vehicles == 1)
            { // add
                char query[256];
                char reg_no[100];
                char type[100];
                printf("Enter vehicle registration number: ");
                scanf("%s", &reg_no);
                printf("Enter vehicle type : ");
                scanf("%s", &type);

                // sprintf(query, "select reg_no from vehicles where reg_no ='%%%s%%' ",reg_no);

                sprintf(query, "INSERT INTO vehicles (reg_no, type) VALUES ('%s', '%s')", reg_no, type);

                // Executing SQL query
                if (mysql_query(conn, query) != 0)
                {
                    printf("Vehicle save failed..\n");
                    fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
                }
                else
                {
                    printf("Vehicle saved successfully..\n");
                }
            }
            // search vehicle
            else if (choice_vehicles == 2)
            {
                char query[256];
                char reg_no[100];
                printf("Please enter vehicle registration number: ");
                scanf("%99s", &reg_no);
                snprintf(query, sizeof(query), "SELECT * FROM `vehicles` WHERE reg_no LIKE '%%%s%%'", reg_no);

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
                    printf("%-12s| ", fields[i].name);
                }
                printf("\n");

                // Fetch and print the result rows
                while ((row = mysql_fetch_row(res)))
                {
                    for (int i = 0; i < num_fields; i++)
                    {
                        printf("%-12s| ", row[i] ? row[i] : "NULL");
                    }
                    printf("\n");
                }
            }
            else if (choice_vehicles == 3)
            { // UPDATE `vehicles`
                char query[256];
                int id;
                char reg_no[100]; // Adjust size as needed
                int type[100];
                double unit_price;
                double total_price;
                // Prompt user for item id to update
                printf("Please enter item id: ");
                scanf("%d", &id);

                // Prompt user for new values
                printf("Please enter new reg_no: ");
                scanf("%99s", reg_no); // Limit input to prevent buffer overflow

                printf("Please enter new type: ");
                scanf("%99s", type); // Limit input to prevent buffer overflow

                // Format the update query
                snprintf(query, sizeof(query),
                         "UPDATE `vehicles` SET reg_no='%s' ,type='%s' WHERE id=%d",
                         reg_no, type, id);

                // Execute the query
                if (mysql_query(conn, query))
                {
                    fprintf(stderr, "Update query failed: %s\n", mysql_error(conn));
                }
                else
                {
                    printf("Record updated successfully.\n");
                }

            } // delete vehicle
            else if (choice_vehicles == 4)
            {
                char reg_no[100];
                char query[256];
                printf("Please enter vehicle reg number\n");
                scanf("%s", reg_no);
                snprintf(query, sizeof(query), "DELETE FROM `vehicles` WHERE reg_no = '%s'", reg_no);

                // Execute the query
                if (mysql_query(conn, query))
                {
                    fprintf(stderr, "Vehicle delete query failed: %s\n", mysql_error(conn));
                }
                else
                {
                    printf("Vehicle deleted successfully.\n");
                }
            }
            else if (choice_vehicles == 5)
            {
                int vehicle_id;
                int item_id;
                int loop_for_item_loading;
                double qty;
                char query[256];
                printf("**Item load section**\n\n\n");

                printf("**Available vehicles list**\n");

                snprintf(query, sizeof(query), "SELECT * FROM `vehicles` ");

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
                    printf("%-12s| ", fields[i].name);
                }
                printf("\n");

                // Fetch and print the result rows
                while ((row = mysql_fetch_row(res)))
                {
                    for (int i = 0; i < num_fields; i++)
                    {
                        printf("%-12s| ", row[i] ? row[i] : "NULL");
                    }
                    printf("\n");
                }

                printf("Please enter vehicle id for loading to items: ");
                scanf("%d", &vehicle_id);

                snprintf(query, sizeof(query), "SELECT COUNT(*) FROM vehicles WHERE id = '%d'", vehicle_id);

                if (mysql_query(conn, query))
                {
                    fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
                    // return;
                }

                MYSQL_RES *result = mysql_store_result(conn);
                if (!result)
                {
                    fprintf(stderr, "Failed to store result: %s\n", mysql_error(conn));
                    // return;
                }

                MYSQL_ROW row = mysql_fetch_row(result);
                if (!row)
                {
                    fprintf(stderr, "Failed to fetch row: %s\n", mysql_error(conn));
                    mysql_free_result(result);
                    // return;
                }

                // Check if the count is greater than 0
                int count = atoi(row[0]);
                mysql_free_result(result);
                if (!(count > 0))
                {
                    printf("WARNING!!\n Vehicle id is not matching with our records.\nPlease check vehicle table and try again..!\n");
                }
                else
                {

                    printf("**Available items list**\n");

                    available_items();
                    printf("Please enter item id for loading to vehicle: ");
                    scanf("%d", &item_id);

                    // Items validation start
                    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM item WHERE id = '%d'", item_id);

                    if (mysql_query(conn, query))
                    {
                        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
                        // return;
                    }

                    MYSQL_RES *result = mysql_store_result(conn);
                    if (!result)
                    {
                        fprintf(stderr, "Failed to store result: %s\n", mysql_error(conn));
                        // return;
                    }

                    MYSQL_ROW row = mysql_fetch_row(result);
                    if (!row)
                    {
                        fprintf(stderr, "Failed to fetch row: %s\n", mysql_error(conn));
                        mysql_free_result(result);
                        // return;
                    }

                    // Check if the count is greater than 0
                    int count = atoi(row[0]);
                    mysql_free_result(result);
                    if (!(count > 0))
                    {
                        printf("WARNING!!\n Item id is not matching with our records.\nPlease check item table and try again..!\n");
                    }
                    else
                    {

                        printf("Please enter quantity: ");
                        scanf("%lf", &qty);
                        // snprintf(query, sizeof(query), "SELECT COUNT(*) FROM item WHERE id = '%d'", item_id);

                        sprintf(query, "SELECT qty , CASE WHEN qty > '2' then '1' ELSE '0' END AS message FROM item WHERE id = '%d'", item_id);

                        // Execute the query
                        if (mysql_query(conn, query))
                        {
                            fprintf(stderr, "SELECT query failed: %s\n", mysql_error(conn));
                            mysql_close(conn);
                            // return;
                        }

                        // Store the result
                        res = mysql_store_result(conn);
                        if (res == NULL)
                        {
                            fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
                            mysql_close(conn);
                            // return;
                        }

                        // Fetch and print the result
                        // qty validation start
                        row = mysql_fetch_row(res);
                        if (row != NULL)
                        {
                            // printf("Qty: %s, Message: %s\n", row[0], row[1]);

                            double available_qty = atoi(row[0]);

                            if (available_qty >= qty)
                            {
                                sprintf(query, "INSERT INTO loading (vehicle_id, item_id,qty,day_type) VALUES ('%d', '%d' , '%lf' , 'morning')", vehicle_id, item_id, qty);


// UPDATE item SET qty = (qty - 1) WHERE id = 1;
                                if (mysql_query(conn, query) != 0)
                                {
                                    printf("Items loading failed..\n");
                                    fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
                                }
                                else
                                {
                                    printf("Items loading to vehicle successfully..\n");
                                }



                                // sprintf(query, "UPDATE item SET qty = (qty - '%lf') WHERE id = '%d'",item_id,qty);
                                sprintf(query, "UPDATE item SET qty = qty - %lf WHERE id = %d", qty, item_id);
sprintf(query, "UPDATE item SET qty = qty - %lf WHERE id = %d", qty, item_id);

                                if (mysql_query(conn, query) != 0)
                                {
                                    // printf("Items loading failed..\n");
                                    fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
                                }
                                else
                                {
                                    // printf("Items loading to vehicle successfully..\n");
                                }



                            }
                            else
                            {
                                printf("insufficient quantity. Please check the item table and try again\n");
                            }
                        }
                        else
                        {
                            printf("No result found for the given item_id.\n");
                        } // qty validation end

                    } // Items validation end
                } // vehicle validation end
            }
            else if (choice_vehicles == 6)
            {
                printf("**Item unload section**\n");
            }
        } // Add purchasing
        else if (choice == 3)
        {
            printf("**Add purchasing items from suppliers**\n");
            char query[256];
            char itemname[100];
            char supplier_name[100];
            double qty;
            double unit_price;
            printf("Enter item name: ");
            scanf("%s", &itemname);
            printf("Enter supplier name : ");
            scanf("%s", &supplier_name);
            printf("Enter qty:");
            scanf("%lf", &qty);
            printf("Enter unit price : ");
            scanf("%lf", &unit_price);

            // sprintf(query, "select reg_no from vehicles where reg_no ='%%%s%%' ",reg_no);

            sprintf(query, "INSERT INTO suppliers (item_name, supplier_name,qty,unit_price) VALUES ('%s', '%s' , '%.2f' , '%.2f')", itemname, supplier_name, qty, unit_price);

            // Executing SQL query
            if (mysql_query(conn, query) != 0)
            {
                printf("Supplier save failed..\n");
                fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
            }
            else
            {
                printf("Supplier saved successfully..\n");
            }
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
        DBA();
    }
    else
    {

        printf("Please enter valid input values.\n e.g 1 or 2\n");
    }

    // DBA();
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
