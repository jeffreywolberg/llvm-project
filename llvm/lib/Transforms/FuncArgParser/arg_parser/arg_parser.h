#define IS_PTR 0x0001 // has * in data type
#define IS_STRUCT 0x0002 // ptr to a struct
#define IS_FUNCTION 0x0004 // ptr to a function
#define IS_UNION 0x0008 // ptr to a union

struct llvm_arg {
	char[100] funcName;
	char argNo;
	char[50]; llvm_type; // i32, double, %struct.my_struct*
	unsigned long flags; // see IS_XXXX above
};
