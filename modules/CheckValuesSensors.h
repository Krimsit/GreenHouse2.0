// float* CheckValuesSensors(float *arr, float *Norms){
// 	// float tmp[4];
// 	// for(int i = 0; i < 4; i++){
// 	// 	tmp[i] = Norms[i] - arr[i];
// 	// }
// 	// return tmp;
// 	return arr;
// }

float* CheckValuesSensors(float* arr, int size, float *Norms)
{
    float *tmp = new float[size];
    for(int i = 0; i < size; i++){
			tmp[i] = Norms[i] - arr[i];
		}
    return tmp;
}