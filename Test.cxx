#include "tensorflow.h"
#include <iomanip>
using namespace std;
void plotLoss(const Array<float>& history, int width = 50, int height = 10) {
    float maxL = -1e9, minL = 1e9;
    for(float l : history) {
        if(l > maxL) maxL = l;
        if(l < minL) minL = l;
    }

    std::cout << "\nLoss Curve (" << minL << " to " << maxL << "):\n";
    for (int i = height; i >= 0; i--) {
        float threshold = minL + (maxL - minL) * (float)i / height;
        std::cout << (threshold < 10 ? " " : "") << std::fixed << std::setprecision(2) << threshold << " | ";
        for (int j = 0; j < history.len(); j++) {
            if (history[j] >= threshold) std::cout << "*";
            else std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "       " << std::string(history.len(), '-') << "\n";
}
int main(int argc, char *argv[])
{
	Array2d<float> t({{1,2,3},{1,3,2},{4,5,6}});
	Array2d<float> in(3,9,{-1,1});
	Array2d<float> inTest(1,9,{-1,1});
	Array<float> losses;
	Dense m(9,12);
	Dense n(12,9);
	Dense p(9,3);
	for(int i=0;i<20;i++){
		Array2d<float> pred1=m(in);
		Array2d<float> pred2=n(pred1);
		Array2d<float> pred = p(pred2);
		Array2d<float> error = pred-t;
		float loss = (sum(error[0]*error[0])+sum(error[1]*error[1])+sum(error[2]*error[2]))/3.0;
		losses.append(loss);
		Array2d<float> grad = p.update(error, 0.01);
		Array2d<float> grad1 = n.update(grad, 0.01);
		Array2d<float> grad2 = m.update(grad1, 0.01);
		}
	cout<<"training done"<<endl;
	plotLoss(losses);
	Array2d<float> pred1=m(inTest);
		Array2d<float> pred2=n(pred1);
		Array2d<float> pred = p(pred2);
		Array<float> error = pred[0]-t[0];
	cout<<"Difference :	"<<sum(error)<<endl;
	return 0;
}