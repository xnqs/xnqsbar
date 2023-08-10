namespace xnqs {
// finds the "index" of the msb, or floor(log2(val)) if you will
// O(log(logN))
int msb(int val) {
	int ret = 0;
	for (int step = 16; step > 0; step >>= 1) {
		if (val>>(ret+step)) {
			ret += step;
		}
	}
	return ret;
}
} // namespace xnqs
