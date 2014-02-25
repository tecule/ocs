char *encode_unsigned(unsigned value) {
	int num_digits = 0;
	while (value > 0) {
		value /= 10;
		num_digits++;
	}
}
