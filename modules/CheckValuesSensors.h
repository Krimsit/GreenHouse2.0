float* CheckValuesSensors(float *arr, int n, float *Norms){
	float tmp[n];
	for(int i = 0; i < n; i++){
		tmp[i] = Norms[i] - arr[i];
	}
	return tmp;
}