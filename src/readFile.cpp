#include "./headers/common.h"
void readFile(string filename, int &matrix[])
{
	int N;
	string tag, value="	";
	string type;
	string format;
	while(value.size() > 0) {
		cin<<tag;
		getline(cin, value);
		while(value[0] == ' ' || value[0] == ':') {
			value = value.substr(1);
		}
		if(tag == "DIMENSION") {
			N = (int) value;
		} else if(tag == "EDGE_WEIGHT_TYPE") {
			type = value;
			if(value=="EUC_2D") float pos[N][2];
		} else if(tag == "EDGE_WEIGHT_FORMAT") {
			format = value;
		}
	}
	if(type == "EUC_2D") { // Euclidian coordinates
		int i = 0;
		while(i<N) {
			cin>> i>>pos[i-1][0]>>pos[i-1][1];
		}
		for(int i = 0; i<N;i++) {
			for(j = 0; j<i; j++) {
				float xd = pos[i][0] - pos[j][0];
				float yd = pos[i][1] - pos[j][1];
				matrix[i*N+j] = matrix[j*N+i] = nint( sqrt(xd*xd + yd*yd) );
			}
			matrix[i*N+i] = 0;
		}
		
	} else if(type=="EXPLICIT" && format="LOWER_DIAG_ROW") { // Lower triangular
		for(int i=0; i<N;i++) {
			for(int j = 0; j<i; j++) {
				cin>>matrix[i*N +j];
				matrix[N*j+i] = matrix[i*N+j];
			}
			cin>>matrix[i*N+i];
		}
	}
}
