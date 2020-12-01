   n = 6;
   d = rand(n,1); % The diagonal values
   t = triu(bsxfun(@min,d,d.').*rand(n,1)); % The upper trianglar random values
   M = diag(d)+t+t.'; % Put them together in a symmetric matrix
   
   for i=1:n
       M(i,i)=M(i,i)+i;
   end
   T=hess(M);
   Tc=T;