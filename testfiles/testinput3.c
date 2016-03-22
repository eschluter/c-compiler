int testfunc ();
int testfunc2 (int one, int two);

int testfunc() {
	int i;
	i = i + 1;
}

int testfunc2 (int one, int two) {
	one = two + 1;
}

extern int printf (string s);

int main () {
	string u, v;
	u = "this is it";
	v = "and this too\n";

	printf (v);
	printf (u+v);

	if (u != v)
		printf (u);
	else
		printf (v);
	return 0;
}	
