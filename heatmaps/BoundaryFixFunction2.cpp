//============================================================================
// Name        : BoundaryFix2.cpp
// Author      : bkatigb
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdio.h>

#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <fts.h>
#include <sstream>


#include "BoundaryFix.h"

using namespace std;

int intersect(int s1x0,int s1y0,int s1x1,int s1y1,int s2x0,int s2y0,int s2x1,int s2y1)
{
	int dy,dx;
	float fx,y,m,x,b;
	if (s1x0==s2x0 && s1y0==s2y0)
	{
		return 0;
	}
//	cout << s2x0 << "," << s2y0 << endl;
	if (s1x0==s1x1 && s1x0==s2x0)
	{
		if ((s2y0<s1y0 && s2y0>s1y1) ||
		    (s2y0>s1y0 && s2y0<s1y1))
		{
//			cout << "xx" << endl;
			return 0;
		}
		else
		{
//			cout << " @1 " ;
			return 2;
		}
	}
	if (s1y0==s1y1 && s1y0==s2y0)
	{
		if ((s2x0<s1x0 && s2x0>s1x1) ||
		    (s2x0>s1x0 && s2x0<s1x1))
		{
//			cout << "yy" << endl;
		return 0;
		}
		else
		{
//			cout << " @2 " ;
			return 2;
		}
	}

	if (s1x1==s2x0 && s1y1==s2y0)
	{
//		cout << " @3 " ;
		return 2;
	}


	dy = s1y1 - s1y0;
	dx = s1x1 - s1x0;

//	if (dx==0)
//	{
//		cout << " @4 " ;
//		return 2;
//	}

//	m = dy / dx;
//	b = s1y0 - (m * s1x0);
//	y = (m * s2x0) + b;
//	cout << s2x0 << "," << s2y0 << " computed y: " << y << endl;
//	fx = s2y0;
//	if (fx == y )
//	{
//		    cout<< "fx " << s1x0 << "," << s1y0;
//		    cout<< " " << s1x1 << "," << s1y1;
//		    cout<< " " << s2x0 << "," << s2y0;
//			cout<< " " << s2x1 << "," << s2y1 << " computed y: " << y << endl;
//		return 1;
//	}


	    float nume_a =  ((s2x1-s2x0)*(s1y0-s2y0)-(s2y1-s2y0)*(s1x0-s2x0));
	    float nume_b =  ((s1x1-s1x0)*(s1y0-s2y0)-(s1y1-s1y0)*(s1x0-s2x0));
	    float deno   =  ((s2y1-s2y0)*(s1x1-s1x0)-(s2x1-s2x0)*(s1y1-s1y0));
	    float ua     = 999.999999;
	    float ub     = 999.999999;
		if (deno > -0.0009 && deno < 0.0009)
		{
			deno = 0;
		}
		if (nume_a > -0.0009 && nume_a < 0.0009)
		{
			nume_a = 0;
		}
		if (nume_b> -0.0009 && nume_b < 0.0009)
		{
			nume_b = 0;
		}
	    if (deno != 0)
	    {
	    	ua = nume_a / deno;
	    	ub = nume_b / deno;
	    	if (ua>-0.0009 && ua < 0.0009)
	    	{
	    		ua=0;
	    	}
	    	if (ub>-0.0009 && ub < 0.0009)
	    	{
	    		ub=0;
	    	}
//	    	cout<< " ua: " << ua << "ub: " << ub;
//	    	if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1)
	    	if (ua >= 0 && ua <= 1 && ub == 0 )
	    	{
//				cout<< "ua: " << ua << "ub: " << ub << "fx " << s1x0 << "," << s1y0;
//				cout<< " " << s1x1 << "," << s1y1;
//				cout<< " " << s2x0 << "," << s2y0;
//				cout<< " " << s2x1 << "," << s2y1 << " computed y: " << y << endl;
	    		return 1;
	    	}

	    	if (ua == 1 && ub >= 0 && ub <= 1)
	    	{
//				cout<< "ua: " << ua << "ub: " << ub << "fx " << s1x0 << "," << s1y0;
//				cout<< " " << s1x1 << "," << s1y1;
//				cout<< " " << s2x0 << "," << s2y0;
//				cout<< " " << s2x1 << "," << s2y1 << " computed y: " << y << endl;
	    		return 1;
	    	}

	    	if (ua > 0 && ua < 1 && ub > 0 && ub < 1 )
//	    	if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1 )
	    	{
//				cout<< "ua: " << ua << "ub: " << ub << "fx " << s1x0 << "," << s1y0;
//				cout<< " " << s1x1 << "," << s1y1;
//				cout<< " " << s2x0 << "," << s2y0;
//				cout<< " " << s2x1 << "," << s2y1 << " computed y: " << y << endl;
	    		return 1;
	    	}

	    }


//	    cout << " @5 " ;
	return 2;
}

/* Process boundary round 2 - output tileID with markup */
void processBoundaryFixing2(stringstream &instream, stringstream &outstream)
{
	vector<points> coord;
	vector<points> coord2;
	int minX, minY, maxX, maxY;

	/*data id*/
	string rec_id;
	int orig_item_cnt,item_out_cnt;

	string str,xp,yp,sv_rec_id;	

	int pos1,pos2,eol_ch;
	bool f1st=true;
	bool cont=false;
	points pt;

	f1st = true;
	int resp=0;
	int ctr0=0;
	int ctr1=0;
	int ctr2=0;
	int ln_ctr=0;
	int s1x0,s1x1,s1y0,s1y1,s2x0,s2x1,s2y0,s2y1;


	bool b = false;
	bool proc = false;
	bool loop = true;

	while (instream.good())
	{
		instream >> str;
		if (f1st)
		{
			pos1 = str.find(';');
			if (pos1 > 0)
			{
			sv_rec_id = str;
			}
			f1st = false;
			ctr0 = 0;
		}
		pos1 = str.find(',');
		pos2 = str.size() - 1;
		eol_ch = instream.peek();

		if (pos1 != pos2 && pos1>0)
		{
			xp    = str.substr(0,pos1);
			yp    = str.substr(pos1+1,pos2-pos1);
			pt.x  = strtod(xp.c_str(),NULL);
			pt.y  = strtod(yp.c_str(),NULL);
			coord.push_back(pt);
			coord2.push_back(pt);
		}
		if (eol_ch==10 || eol_ch==13)
		{
			loop = true;
			while (loop)
			{
			loop = false;
			rec_id        = sv_rec_id;
			ctr0 = coord.size();

			if (ctr0 >= 4)
			{
				proc = true;
			}
			else
			{
				proc = false;
			}

			if (proc)
			{
				/*remove self_intersection*/
//				cout << "ctr0: " << ctr0 << endl;
				for (int i=0;i!=ctr0-1 && i<ctr0-1;i++)
				{
//					cout << endl << "1st: " << i;
					ctr2 = coord2.size();
					cont = true;
					for (int j=i+1;j!=ctr2-1 && j<ctr2-1 && cont;j++)
					{
//						cout << " " << j;
//						if (i!=j)
						{
							s1x0 = coord[i].x;
							s1y0 = coord[i].y;
							s1x1 = coord[i+1].x;
							s1y1 = coord[i+1].y;

							s2x0 = coord2[j].x;
							s2y0 = coord2[j].y;
							s2x1 = coord2[j+1].x;
							s2y1 = coord2[j+1].y;

//							if (s1x1==68168 &&
//								s1x0==68168 &&
//								s1y1==9840 &&
//								s1y0==9837)
							{
							resp = intersect(s1x0,s1y0,s1x1,s1y1,s2x0,s2y0,s2x1,s2y1);
//							cout << " resp: " << resp;
							if (resp==0)
							{
//								cout << j << " 1del " << coord2[j].x << "," << coord2[j].y << endl;
								coord2.erase(coord2.begin()+j);
								ctr2 = coord2.size();
								cont = false;
								loop = true;
							}
							if (resp==1)
							{
//								cout << j+1 << " 2del " << coord2[j+1].x << "," << coord2[j+1].y << endl;
								coord2.erase(coord2.begin()+j);
								ctr2 = coord2.size();
								cont = false;
								loop = true;
							}
							}
						}
					}
				}

				ctr2 = coord2.size();
				if (ctr2 >= 4)
				{
					proc = true;
				}
				else
				{
					proc = false;
				}
			}

			if (proc)
			{
				/*remove self_intersection 2nd pass*/
				coord.clear();
				ctr0 = coord2.size();
				for (int k=0;k!=ctr0;k++)
				{
					coord.push_back(coord2[k]);
				}
				ctr0 = coord.size();
//				cout << "ctr0: " << ctr0 << endl;
				for (int i=ctr0-1;i!=0 && ctr0>1;--i)
				{
//					cout << "2nd: " << i << endl;
					ctr2 = coord2.size();
					cont = true;
					for (int j=i-1;j!=1 && j>1 && cont;--j)
					{
						s1x0 = coord[i].x;
						s1y0 = coord[i].y;
						s1x1 = coord[i-1].x;
						s1y1 = coord[i-1].y;

						s2x0 = coord2[j].x;
						s2y0 = coord2[j].y;
						s2x1 = coord2[j-1].x;
						s2y1 = coord2[j-1].y;

						resp = intersect(s1x0,s1y0,s1x1,s1y1,s2x0,s2y0,s2x1,s2y1);
						if (resp==0)
						{
//							cout << j << " 3del " << coord2[j].x << "," << coord2[j].y << endl;
							coord2.erase(coord2.begin()+j);
							ctr2 = coord2.size();
							cont = false;
							loop = true;
						}
						if (resp==1)
						{
//							cout << j+1 << " 4del " << coord2[j+1].x << "," << coord2[j+1].y << endl;
							coord2.erase(coord2.begin()+j);
							ctr2 = coord2.size();
							cont = false;
							loop = true;
						}
					}
				}

				ctr2 = coord2.size();
				if (ctr2 >= 4)
				{
					proc = true;
				}
				else
				{
					proc = false;
				}
			}

            if (loop)
            {
            	proc = false;
            	coord.clear();
            	for (int i=0;i!=ctr2;i++)
            	{
            		coord.push_back(coord2[i]);
            	}
            	coord2.clear();
            	for (int i=0;i!=ctr2;i++)
            	{
            		coord2.push_back(coord[i]);
            	}
            }

			if (proc)
			{
				ctr1 = coord2.size();
				// cout << rec_id;
				/* Output tile ID instead */
				int t;

				outstream << "POLYGON((";
				for (t=0;t<ctr1;t++)
				{
					if (t != ctr1 - 1) {
						outstream  << coord2[t].x << " " << coord2[t].y << ", ";
					} else {

						outstream  << coord2[t].x << " " << coord2[t].y;
					}
				}
				outstream << "))" << endl;
				coord.clear();
				coord2.clear();
			}

			f1st = true;

			} /*inner do-loop*/
			coord.clear();
			coord2.clear();
		} /*eol*/

	} /*while good*/
	outstream.clear();
	coord.clear();
	coord2.clear();

}
