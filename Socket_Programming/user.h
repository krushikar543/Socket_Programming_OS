struct single_user{
    char username[50];
    char password[20];
    int bal;
    char email_id[50];
    char ph_no[10];
    int flag;
};
struct U{
    char username[50];
    char password[20];
    char ph_no[10];
    char email_id[50];
};
struct joint_user{
    int flag;
    int count;
    struct U u[2];
    int bal;
};
struct admin{
    int flag;
    char username[50];
    char password[20];
};