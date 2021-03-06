#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericMatrix ItemSimil(NumericMatrix x) {
  
  int numItem = x.ncol();
  int numUser = x.nrow();
  
  NumericMatrix sim(numItem, numItem);
  
  
  double s;//sum of products between item i and j
  double s_i;// sum of squares of scores on item i;
  double s_j;// sum of squares of scores on imte j;
  
  for (int i = 1; i < numItem; i++){
    
    for (int j = 0; j < i; j++){
       
      s = 0;
      s_i = 0;
      s_j = 0;
      
      for(int u = 0; u < numUser; u++){
        
        if( !R_IsNA( x(u,i) )  &&  !R_IsNA( x(u,j) ) ) {
          
          s += x(u,i) * x(u,j);
          s_i += x(u,i) * x(u,i);
          s_j += x(u,j) * x(u,j);
          
        }
        
      }
      
      if((s_i != 0) && (s_j != 0)){
        
        sim(i,j) = s/sqrt(s_i * s_j);
        //symmetry
        sim(j,i) = sim(i,j);
        
      }
      
    }
    
  }
  
  return sim;
  
}
