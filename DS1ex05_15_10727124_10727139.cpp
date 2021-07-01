// 10727124 ¼B¦t§Ê 10727139 Ä¬±R³Ç

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
using namespace std ;

typedef char Str [1000] ;
int N ;

struct Item {
  Str data ; 
  int graduaters ;
};

void Swap( Item &a, Item &b ) {
  Item temp ;

  strcpy(temp.data, a.data ) ;
  strcpy(a.data, b.data ) ;
  strcpy(b.data, temp.data ) ;

  temp.graduaters = a.graduaters ;
  a.graduaters = b.graduaters ;
  b.graduaters = temp.graduaters ;
}

int SetNumber( Str a ) {
	int tabN = 0 ;
	int num = 0 ;
	int i = 0 ;
	
	while ( tabN < 8 ) {
		if ( a[i] == '\t' ) {
			tabN++ ;
		}
		i++ ;
	}
	
	while ( a[i] != '\t' ) {
		num = num *10 + ( a[i] - '0' ) ;
		i++ ;
	}
	return num ;	
}

bool ReadFile( string filename, vector<Item> &list ) {
  FILE *infile = fopen( filename.c_str(), "r" ) ;

  if ( infile == NULL ) {
    cout << endl << filename << " does not exist!\n" ;
    return false;
  }
  else {
    Item temp ;
    Str title ;

    fscanf( infile, "%[^\n]%*c", &title ) ;     // Åý©S?
    fscanf( infile, "%[^\n]%*c", &title ) ;     // Åý©S?
    fscanf( infile, "%[^\n]%*c", &title ) ;     // Åý©S?

    for ( int i = 1; fscanf( infile, "%[^\n]%*c", &temp.data ) != EOF ; i++ ){
      temp.graduaters =  SetNumber( temp.data ) ; 

      N = i;
      list.push_back( temp ) ;
    }
  }
  return true ;
}

void SelectSort( vector<Item> &list ) {
  int max ;
  for( int i = 0 ; i < N-1 ; i++ ){
    max = i ;
    for( int j = i + 1 ; j < N  ; j++ ){
      if ( list[j].graduaters > list[max].graduaters ){
      max = j ;
      }
    }
    Swap( list[i], list[max] ) ;
  }
}

void BubbleSort( vector<Item> &list ) {
  bool stop = true ;

  for ( int i = 0 ; i < N ; i++ ) {
    stop = true ;
    for( int j = 0 ; j < N-1-i ; j++ ) {
      if ( list[j].graduaters < list[j+1].graduaters ) {
        Swap( list[j], list[j+1] ) ;
        stop = false ;
      }
    }
    if ( stop ) {
      break ;
    }
  }
}

void Merge( vector<Item> &list, int first, int mid, int last ){
  int first1 = first, last1 = mid;
  int first2 = mid+1, last2 = last;
  int i = 0;
  Item tempitem;
  vector<Item>  temp;
  
  while( ( first1 <= last1) && ( first2 <= last2) ){
    if ( list[first1].graduaters > list[first2].graduaters ){
      temp.push_back( list[first1] );
      first1++;
    }
    else {
      temp.push_back( list[first2] );
      first2++;
    }
  }


  if ( first1 > last1 ){
    while ( first2 <= last2 ){
      temp.push_back( list[first2] );
      first2++;
    }
  }
  else if ( first2 > last2 ){
    while ( first1 <= last1 ){
      temp.push_back( list[first1] );
      first1++;
    }
  }
  
  int m = 0;
  while ( first <= last  ){
    list[first] = temp[m];
    m++;
    first++;
  }
}

void MergeSort( vector<Item> &list, int first, int last ){
  if ( first < last ){
    int mid = ( first + last ) / 2;
    MergeSort( list, first, mid );
    MergeSort( list, mid+1, last );
    Merge( list, first, mid, last );
  }
}

void Partition( vector<Item> &list, int first, int last, int &pivot ){
  pivot = first;
  int unknown = pivot+1;
  
  while ( unknown <= last ){
    if ( list[unknown].graduaters > list[pivot].graduaters ){
      Swap( list[unknown], list[pivot] );
      Swap( list[unknown], list[pivot+1] );
      pivot++;
    }
    unknown++;
  }
}


void QuickSort( vector<Item> &list, int first, int last ){
  int pivotindex;
  
  if ( first < last ){
    Partition( list, first, last, pivotindex );
    QuickSort( list, first, pivotindex-1 );
    QuickSort( list, pivotindex+1, last );
  }
}

void WriteFile( string filename, vector<Item> list ) {
  FILE  *outfile = fopen( filename.c_str(), "w" );

  int i = 0 ;
  while ( i < N ) {
	fprintf( outfile, "%s\n", list[i].data ) ;
	i++ ;
  }
  fclose( outfile );
}

void WriteFileForRadix( string filename, vector<Item> list ) {
  FILE  *outfile = fopen( filename.c_str(), "w" );

  int i = N-1 ;
  while ( i >= 0 ) {
	fprintf( outfile, "%s\n", list[i].data ) ;
	i-- ;
  }
  fclose( outfile );
}

void RadixSort( vector<Item> &list, int base ){
  if ( base < 1000 ){
    int x = 0;	
    int type[10] = {0};
    
    Item temp[N];
    for( int i = 0; i < N ; i++){
      if ( (list[i].graduaters % base) - (list[i].graduaters % ( base / 10 ) )== 0 ){
        type[0]++;	
	  }
	  else if ( (list[i].graduaters % base) - (list[i].graduaters % ( base / 10 ) )== 1 ){
        type[1]++;	
	  }
	  else if ( (list[i].graduaters % base) - (list[i].graduaters % ( base / 10 ) )== 2 ){
        type[2]++;	
	  }
	  else if ( (list[i].graduaters % base) - (list[i].graduaters % ( base / 10 ) )== 3 ){
        type[3]++;	
	  }
	  else if ( (list[i].graduaters % base) - (list[i].graduaters % ( base / 10 ) )== 4 ){
        type[4]++;	
	  }
	  else if ( (list[i].graduaters % base) - (list[i].graduaters % ( base / 10 ) )== 5 ){
        type[5]++;	
	  }
	  else if ( (list[i].graduaters % base) - (list[i].graduaters % ( base / 10 ) )== 6 ){
        type[6]++;	
	  }
	  else if ( (list[i].graduaters % base) - (list[i].graduaters % ( base / 10 ) )== 7 ){
        type[7]++;	
	  }
	  else if ( (list[i].graduaters % base) - (list[i].graduaters % ( base / 10 ) )== 8 ){
        type[8]++;	
	  }
	  else if ( (list[i].graduaters % base) - (list[i].graduaters % ( base / 10 ) )== 9 ){
        type[9]++;	
	  }	
    }
  
    type[0] = type[0] - 1;
    type[1] = type [0] + type [1];
    type[2] = type [1] + type [2];
    type[3] = type [2] + type [3];
    type[4] = type [3] + type [4];
    type[5] = type [4] + type [5];
    type[6] = type [5] + type [6];
    type[7] = type [6] + type [7];
    type[8] = type [7] + type [8];
    type[9] = type [8] + type [9];
    type[0]++;
    type[1]++;
    type[2]++;
    type[3]++;
    type[4]++;
    type[5]++;
    type[6]++;
    type[7]++;
    type[8]++;
        type[9]++;

    for( int j = 0; j <= N ; j++){
      
  	  if ( (list[j].graduaters % base) - (list[j].graduaters % ( base / 10 ) )== 0 ){
        temp[ x ] = list[j];
	    x++;	
  	  }
	  else if ( (list[j].graduaters % base) - (list[j].graduaters % ( base / 10 ) )== 1 ){
	  	
        temp[ type[0] ] = list[j];
	    type[0]++;	
  	  }
	  else if ( (list[j].graduaters % base) - (list[j].graduaters % ( base / 10 ) )== 2 ){
	  	
        temp[ type[1] ] = list[j];
	    type[1]++;	
	  }
	  else if ( (list[j].graduaters % base) - (list[j].graduaters % ( base / 10 ) )== 3 ){
	  	
        temp[ type[2] ] = list[j];
	    type[2]++;	
	  }
	  else if ( (list[j].graduaters % base) - (list[j].graduaters % ( base / 10 ) )== 4 ){
	  	
        temp[ type[3] ] = list[j];
	    type[3]++;	
	  }
	  else if ( (list[j].graduaters % base) - (list[j].graduaters % ( base / 10 ) )== 5 ){
	    
        temp[ type[4] ] = list[j];
	    type[4]++;	
	  }
	  else if ( (list[j].graduaters % base) - (list[j].graduaters % ( base / 10 ) )== 6 ){
	  	
        temp[ type[5] ] = list[j];
	    type[5]++;	
	  }
	  else if ( (list[j].graduaters % base) - (list[j].graduaters % ( base / 10 ) )== 7 ){
	  	
        temp[ type[6] ] = list[j];
	    type[6]++;	
	  }
	  else if ( (list[j].graduaters % base) - (list[j].graduaters % ( base / 10 ) )== 8 ){
	  	
        temp[ type[7] ] = list[j];
	    type[7]++;	
	  }
	  else if ( (list[j].graduaters % base) - (list[j].graduaters % ( base / 10 ) )== 9 ){
	  	
        temp[ type[8] ] = list[j];
	    type[8]++;	
	  }	
    }
    
    for ( int k = 0 ; k <  N ; k++) {
  	  list[k] = temp[k];
    }
     
    RadixSort( list,  base*10 );
  }
}

void RadixSort2( vector<Item> &list, int first, int last ){
	Item temp[10][N] ;
	int max ;
	int counter[10] = {0} ;
	int i, j ;

	for( max = list[first].graduaters, i = first+1 ; i <= last ; i++ ) {
		if ( max < list[i].graduaters ) {
			max = list[i].graduaters ;
		}
	}
		
	for( int base = 1 ; ( max / base ) > 0 ; base = base * 10 ) {
		for( i = first ; i <= last ; i++ ) {
			int LSD = ( list[i].graduaters / base ) % 10 ;
			temp[LSD][counter[LSD]].graduaters = list[i].graduaters ;
			strcpy( temp[LSD][counter[LSD]].data, list[i].data ) ;
			counter[LSD]++ ;
		}
		
		int k = 0 ;
		for( i = 0 ; i < 10 ; i++ ) {
			if ( counter[i] > 0 ) {
				for ( j = 0 ; j < counter[i] ; j++, k++ ) {
					list[k].graduaters = temp[i][j].graduaters ;
     				strcpy( list[k].data, temp[i][j].data ) ;

				}
				counter[i] = 0 ;
			}
		}
	}	
}






int main() {
  string choice, command, filename ;
  vector<Item> list ;
  vector<Item> selectsort ;
  vector<Item> bubblesort ;
  vector<Item> mergesort ;
  vector<Item> quicksort ;
  vector<Item> radixsort ;
  bool readsuccess ;
  clock_t starttime ;
  clock_t endtime ;
  
  cout << "******** Sorting Algorithms *********" << endl;
  cout << "* 0. QUIT                           *" << endl;
  cout << "* 1. Selection sort vs. Bubble sort *" << endl;
  cout << "* 2. Merge sort vs. Quick sort      *" << endl;
  cout << "* 3. Radix sort                     *" << endl;
  cout << "*************************************" << endl;
  cout << "Input a choice(0, 1, 2, 3): " ;
  cin >> choice ;
  
  while ( choice != "0" ){
  	if ( choice == "1" || choice == "2" || choice == "3" ) {
	  cout << "Input 501, 502, ...[0]Quit): ";
      cin >> command ;
	  
	  if ( command == "0") {
		readsuccess = false ;
	  }
	  else {
        filename = "input" + command + ".txt" ;
	    readsuccess = ReadFile( filename, list ) ;
	  }
    }
    else {
      readsuccess = false ;
      cout << "Command does not exit!\n" ;
	}

    if( readsuccess ) {
		if ( choice == "1"){
		  selectsort = list ;
		  starttime = clock();      
		  SelectSort( selectsort ) ;
		  endtime = clock();
		  cout << endl<< "Selection sort: "<< endtime - starttime << " ms" << endl;
		  filename = "select_sortt" + command + ".txt" ;
		  WriteFile( filename, selectsort ) ;

		  bubblesort = list ;
		  starttime = clock();      
		  BubbleSort( bubblesort ) ;
		  endtime = clock();
		  cout << "Bubble sort: "<< endtime - starttime << " ms"<< endl;
		  filename = "bubble_sortt" + command + ".txt" ;
		  WriteFile( filename, bubblesort ) ;
		}
		else if ( choice == "2" ){
		  mergesort = list;
		  starttime = clock();      
		  MergeSort( mergesort,0 , N-1 );
		  endtime = clock();
		  cout << endl<< "Merge sort: " << endtime - starttime << " ms"<< endl;
		  filename = "merge_sortt" + command + ".txt" ;
		  WriteFile( filename, mergesort ) ;

		  quicksort = list;
		  starttime = clock(); 
		  QuickSort( quicksort, 0, N-1 );
		  endtime = clock();
		  cout << "Quick sort: " << endtime - starttime << " ms" << endl;
		  filename = "quick_sortt" + command + ".txt" ;
		  WriteFile( filename, quicksort ) ;
		}
		else if ( choice == "3" ) {
		  radixsort = list;
		  starttime = clock();
		  RadixSort2( radixsort, 0, N-1 );
		  endtime = clock();
		  cout << endl<< "Radix sort: " << endtime - starttime << " ms"<< endl;
		  filename = "radix_sortt" + command + ".txt" ;
		  WriteFileForRadix( filename, radixsort ) ;
			 
		}
		
      list.clear() ;
      selectsort.clear() ;
      bubblesort.clear() ;
      mergesort.clear() ;
      quicksort.clear() ;
      radixsort.clear() ;
    }
    
    cout << endl ;
    cout << "******** Sorting Algorithms *********" << endl;
    cout << "* 0. QUIT                           *" << endl;
    cout << "* 1. Selection sort vs. Bubble sort *" << endl;
    cout << "* 2. Merge sort vs. Quick sort      *" << endl;
    cout << "* 3. Radix sort                     *" << endl;
    cout << "*************************************" << endl;
    cout << "Input a choice(0, 1, 2, 3): " ;
    cin >> choice ;
  }
}
