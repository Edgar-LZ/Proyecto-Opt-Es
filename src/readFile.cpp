#include "./headers/common.h"
#include "./headers/functions.h"

using namespace std;
int * readFile(const string filename, int *N)
{
	string tag, value="	";
	string type;
	string format;
	int * matrix;
	ifstream file; file.open(filename);

	while(value.size() > 0) {
		file>>tag;
		getline(file, value);
		while(value[0] == ' ' || value[0] == ':') {
			value = value.substr(1);
		}
		while(value[value.size()-1] == ' ') {
			value = value.substr(0, value.size()-1);
		}

		if(tag == "DIMENSION" || tag=="DIMENSION:" ) {
			*N = stoi(value);
		} else if(tag == "EDGE_WEIGHT_TYPE" || tag == "EDGE_WEIGHT_TYPE:") {
			type = value;
		} else if(tag == "EDGE_WEIGHT_FORMAT" || tag == "EDGE_WEIGHT_FORMAT:") {
			format = value;
		}
	}
	matrix = (int*) malloc(( (*N)*(*N))*sizeof(int));
	float pos[*N][2];
	if(type == "EUC_2D") { // Euclidian coordinates
		float pos[*N][2];
		int i = 0;
		while(i<(*N)) {
			file>> i>>pos[i-1][0]>>pos[i-1][1];
		}
		for(int i = 0; i<(*N);i++) {
			for(int j = 0; j<i; j++) {
				float xd = pos[i][0] - pos[j][0];
				float yd = pos[i][1] - pos[j][1];
				matrix[i*(*N)+j] = matrix[j*(*N)+i] = round( sqrt(xd*xd + yd*yd) );
			}
			matrix[i*(*N)+i] = 0;
		}
		
	} else if(type=="EXPLICIT" && format=="LOWER_DIAG_ROW") { // Lower triangular
		for(int i=0; i<(*N);i++) {
			for(int j = 0; j<i; j++) {
				file>>matrix[i*(*N) +j];
				matrix[(*N)*j+i] = matrix[i*(*N)+j];
			}
			file>>matrix[i*(*N)+i];
		}
	}
	return matrix;
}
