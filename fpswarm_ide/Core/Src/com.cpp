#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
using namespace std;

class Table {
	public:
		vector<string> attrName;
		vector<vector<string> > data;

		vector<vector<string> > attrValueList;
		void extractAttrValue() {
			attrValueList.resize(attrName.size());
			for(int j=0; j<attrName.size(); j++) {
				map<string, int> value;
				for(int i=0; i<data.size(); i++) {
					value[data[i][j]]=1;
				}

				for(auto iter=value.begin(); iter != value.end(); iter++) {
					attrValueList[j].push_back(iter->first);
				}
			}
		}
};


