function G=makeF(ro, d, u, n)
G=@myfun;

    function F = myfun(x)
        F=0;
        for i=1:n
            F=F+(u(i)*u(i))/(d(i)-x);
        end
        F=F*ro+1;
    end
    
end