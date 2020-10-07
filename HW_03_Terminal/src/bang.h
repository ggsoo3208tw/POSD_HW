class Terminal
{
public:
    // you can use regular expression to get useful token from "Input string"
    Terminal(string instruction): _instruction(instruction)
    {
      // string str1("CircularSector (6,5)");
      // // Input string like this => "Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc"
      std::vector<string>* _strVec=new vector<string>(0);
      // cout<<"Get!:"<<_instruction<<endl;
      cout<<"Inconpelet:"<<isIncompelet(instruction)<<endl;
      if(!isIncompelet(instruction)){
        _strVec=split(instruction,')');

        string *m;


        std::vector<string>::iterator it;
        it=_strVec->begin();
        // ShowList(_strVec);
        check(it,_strVec);
        // ShowList(_strVec);
        // cout<<"--------------"<<endl;
        it=rmSpace(it,_strVec);
        // ShowList(_strVec);
        // cout<<"--------------"<<endl;
        it=filterString(it,_strVec,this->_mark,sizeof(_mark)/sizeof(*_mark),this->_shapeName,sizeof(_shapeName)/sizeof(*_shapeName));

        it=checkFormat(it,_strVec);
        checkMode(_strVec);
        // std::vector<Shape*>::iterator itShape;
        _shapeVec= analysis(it,_strVec);
        // cout<<getFeatur(_mode[1])<<"  "<<getOrder(_mode[2])<<endl;
        _shapeVec = sortShape(_shapeVec,getFeatur(_mode[1]),getOrder(_mode[2]));
        // ShowList(_strVec);
      }else _isThrow=true;

    }
    std::vector<string>::iterator check(std::vector<string>::iterator it,std::vector<string>* vec){
      char c[3]={'T','E','C'};
      for(it=vec->begin();it!=vec->end();it++){
        for(int n=0;n<3;n++){
          if((*it).find(c[n])!=std::string::npos){
            int i=(*it).find(c[n]);
            if((*it)[i-1]==' '){
              // cout<<"yES!"<<endl;
              (*it).erase(0,i);
            }
          }
        }
        // cout<<*it<<endl;
      }



    }
    // string _modeFeature[3]={"area","perimeter","sumOfSquares"};
    // string _modeOrder[2]={"inc","dec"};
    bool isIncompelet(string instruction){//正確回傳0  錯誤回傳1
      // cout<<sizeof(_modeFeature)/sizeof(*_modeFeature)<<endl;
      // cout<<sizeof(_modeOrder)/sizeof(*_modeOrder)<<endl;
        for(string s:_modeFeature){
          if(instruction.find(s) != std::string::npos){
            cout<<"找到"<<s<<endl;
            for(string s1:_modeOrder){
              if(instruction.find(s1) !=std::string::npos ){
                cout<<"找到"<<s1<<endl;
                return false;
              }
              else cout<<"找不到"<<s1<<endl;
            }
          }
          else cout<<"找不到"<<s<<endl;
        }

      return true;
    }
    string getOrder(int mode){
      if(_mode[2]==0) return NULL;
      return _modeOrder[_mode[2]-1];

    }
    string getFeatur(int mode){
      if(_mode[1]==0) return NULL;
      return _modeFeature[_mode[1]-1];
    }

    std::vector<Shape*>* sortShape(std::vector<Shape*>* shapeVec,string featur,string order){
      Sort sort(shapeVec);
      if(order=="inc"){
        AscendingComparison inc(featur);
        std::sort(shapeVec->begin(),shapeVec->end(),inc);
      }
      else if(order=="dec"){
        DescendingComparison dec(featur);
        std::sort(shapeVec->begin(),shapeVec->end(),dec);
      }
      return shapeVec;
    }
    std::vector<Shape*>* analysis(std::vector<string>::iterator it,std::vector<string>* vec){
      std::vector<Shape*>* shapeVec=new vector<Shape*>(0);
      std::vector<Shape*>::iterator itShape=shapeVec->begin();
      shapeVec->clear();
      // shapeVec->push_back(shape_array[i]);

        for(it=vec->begin();it!=vec->end();it++){
          string className=getClassName(*it);
          std::vector<int> numVec=getParameter(*it);
          std::vector<int>::iterator itNum=numVec.begin();
          if(className=="Triangle"){
            // cout<<"new Triangle "<<*itNum<<" "<<*(itNum+1)<<" "<<*(itNum+2)<<" "<<*(itNum+3)<<" "<<*(itNum+4)<<" "<<*(itNum+5)<<endl;
            Triangle *tp;
            try{
              tp=new Triangle(*itNum,*(itNum+1),*(itNum+2),*(itNum+3),*(itNum+4),*(itNum+5));
            }catch(std::string *caught){
              // cout<<"不是三角形!!"<<endl;
              continue;
            }
            shapeVec->push_back(tp);

          }
          else if(className=="Ellipse"){
            // cout<<"new Ellipse "<<*itNum<<" "<<*(itNum+1)<<endl;
            shapeVec->push_back(new Ellipse(*itNum,*(itNum+1)));
            // cout<<shapeVec->at(0)->area()<<endl;
          }
          else if(className=="CircularSector"){
              // cout<<"new CircularSector "<<*itNum<<" "<<*(itNum+1)<<endl;
              shapeVec->push_back(new CircularSector(*itNum,*(itNum+1)));
          }

          }

      return shapeVec;

    }
    string getClassName(string str){
          std::smatch m;
          std::regex e ("\\(");
          std::regex_search ( str, m, e );
            // if (m.ready()) {
              // std::cout << m[0] << " found!\n";
              // std::cout << "prefix: [" << m.prefix() << "]\n";
              // std::cout << "suffix: [" << m.suffix() << "]\n";
              // string s=m.suffix();
            //   for(int i=0;i<s.size();i++)
            //     std::cout << s[i]<<endl;
            // }

      // string s=m.prefix();
      return m.prefix().str();
    }
    std::vector<int> getParameter(string str){//讀取參數 回傳std::vector<int>;
      // cout<<"size="<<str.size()<<endl;
      vector<int> number(0);
      // cout<<str.find('(')<<endl;
      int i;
      string stemp="";
      for(i=str.find('(')+1;i<str.size();i++){
        if(str[i]==',' || str[i]==')'){
          // cout<<stemp<<endl;
          // cout<<"i="<<i<<endl;

          number.push_back(strToInt(stemp));
          stemp="";
        }
        else stemp+=str[i];
      }
      // cout<<stemp<<endl;
      return number;
    }
    int strToInt(string strVal){
      int val;
      istringstream is(strVal);
      is>>val;
      return val;
    }

    void checkMode(std::vector<string>* vec){
        std::vector<string>::iterator it=vec->end()-1;
        // cout<<regex_search(*it,pattern)<<endl;
        // cout<<*it<<endl;
        int i=0;
        for(i=0;i<3;i++){//判斷Feature
          // cout<<"i="<<i<<endl;
          regex pattern(_modeFeature[i]);
          if(regex_search(*it,pattern)){
            // cout<<"find!!:"<<_modeFeature[i]<<endl;
            _mode[1]=i+1;
            break;
          }
        }
        // cout<<"i="<<i<<endl;
        if(i==3){
          // cout<<"_modeFeaturError!!"<<endl;
          _isThrow=true;
          // throw string("Unuseful User Input!");
        }

        i=0;
        for(i=0;i<2;i++){//判斷Order
          // cout<<"i="<<i<<endl;
          regex pattern(_modeOrder[i]);
          if(regex_search(*it,pattern)){
            // cout<<"find!!:"<<_modeOrder[i]<<endl;
            _mode[2]=i+1;
            break;
          }
        }
          // cout<<"i="<<i<<endl;
        if(i==2){
          // cout<<"_modeOderError!!"<<endl;
          _isThrow=true;
          // throw new string("Unuseful User Input!");
        }

        showMode();
    }
    void showMode(){
      // cout<<"Featur:"<<_mode[1]<<endl;
      // cout<<"Order:"<<_mode[2]<<endl;
    }
    std::vector<string>::iterator checkFormat(std::vector<string>::iterator it,std::vector<string>* vec){
      bool run=false;
      for(it=vec->begin();it!=vec->end()-1;){
        for(int i=0;i<3;i++){
            regex pattern(_format[i]);
            if(regex_match(*it, pattern)){
                // cout<<"formatRight!!: "<<*it<<"  "<<_format[i]<<endl;
                run=true;
                break;
            }
        }
        if(run){
          run=false;
          it++;
        }else{
          // cout<<"formatWrong!!:"<<*it<<endl;
          // cout<<"錯誤格式 移除"<<*it<<endl;
          it=vec->erase(it);
        }
      }
      return it=vec->begin();
    }

    std::vector<string>::iterator rmSpace(std::vector<string>::iterator it,std::vector<string>* vec){//remove additional space
      string temp="";
        for(it=vec->begin();it!=vec->end()-1;it++){
          for(char c:(*it)){
            // cout<<(*it)[0]<<endl;
            // cout<<c;
            if(c==' ')continue ;
            else temp+=c;
          }
          // cout<<temp<<endl;
          *it=temp;
          temp="";
        }
        return it=vec->begin();
    }

    std::vector<string>::iterator filterString(std::vector<string>::iterator it ,std::vector<string>* vec,char mark[],int count1,string name[],int count2){//有特殊字元則
      // cout<<"LOG1:"<<count1<<"  "<<count2<<endl;
      //
      // cout<<"LOG1:"<<mark[10]<<endl;
      // cout<<"LOG1:"<<name[2]<<endl;
      for(it=vec->begin();it!=vec->end()-1;){
        // cout<<*it<<endl;
        if(isMark(*it,mark,count1)){
          // cout<<"特殊符號 移除"<<*it<<endl;
          // cout<<"log:"<<*(it-1)<<endl;
          it=vec->erase(it);
        }
        else if(isWrongName(*it,name,count2)){
          // cout<<"名稱錯誤 移除"<<*it<<endl;
          it=vec->erase(it);
        }
        else{
            it++;
            // cout<<"無特殊符號:"<<*it<<endl;
        }
      }
      return it=vec->begin();
    }

    bool isMark(string str,char mark[],int count){
      int i=0;
      // bool run[2]={false,false};
      // // ShowList(_strVec);
      // cout<<"find:"<<str.find("T");
      // char c[3]={'T','E','C'};
      //
      // cout<<str.find("@")<<endl;
      //
      // for(int i=0;i<count;i++){
      //   if(str.find(mark[i]) < )
      //
      //
      // }

      // for(;i<str.find('T'|'E'|);i++);
      //   for(int j=0;j<count;j++)
      //     if(str[i]==mark[j])



      while(!(str.find(mark[i])!= std::string::npos)){
        if(i==count)break;
        i++;
      }
      if(i<count){
        // cout<<"有特殊字元:"<<mark[i]<<endl;
        return 1;
      }
      else{
        // cout<<"無特殊字元"<<endl;
        return 0;
      }
    }

    bool isWrongName(string str,string name[],int count){
      // cout<<"size===="<<count<<endl;
      // cout<<"Name="<<str<<endl;
      std::smatch m;
      std::regex e ("\\(");
      std::regex_search ( str, m, e );
      str=m.prefix();
      // cout<<"Name="<<str<<endl;
      int i=0;
    for(i=0;i<count;i++){
      regex pattern(_shapeName[i]);
      // cout<<str<<"  :  "<<_shapeName[i]<<" ";
      // cout<<regex_match(str,pattern)<<endl;
      if(regex_match(str,pattern))
        break;
      }
      if(i==count){
        // cout<<"log: i="<<i<<endl;
        // cout<<"錯誤名稱"<<endl;
        return 1;
      }
      else{
        // cout<<"正確名稱"<<endl;
        return 0;
      }
    }


    std::vector<string>* split(string instruction,char delimiter){//利用delimiter切割字串
      std::vector<string>* strVec=new vector<string>(0);
      string str;
      strVec->clear();
      // cout<<"_index="<<_index<<endl;
      while(_index < instruction.length()){
        while(instruction[_index] != delimiter && _index < instruction.length()){
          // for(char c:_mark)
          //   if(instruction[_index]==c){
          //     int k=1;
          //     while( !((instruction[_index+k]>=101 && instruction[_index+k]<=132 )|| (instruction[_index+k]>=141 && instruction[_index+k]<=172 )) ){
          //       if(instruction[_index+k]==" ") instruction[_index]
          //
          //     }
          //   }
          // if(instruction[_index]==' ') _index++;
          // cout<<_index<<endl;
          str+=instruction[_index++];
        }
        str+=instruction[_index++];
        strVec->push_back(str);
        // cout<<str<<endl;
        str="";

      }
      // cout<<"final:"<<_index<<endl;
      return strVec;

      // if(s.find(delimiter)==")")
      //   return s.substr(begin, s.find(delimiter)+1);
      // else s.find{
      //   this->_run=false;
      //   cout<<
      // }
    }

    string showResult(){
         // return result For example: [XXX, XXX, XXX]
         cout<<"sdfasdfasfsdf:"<<_isThrow<<endl;
         if(_isThrow) throw string("Unuseful User Input!");

         string result="[";
         for (std::vector<Shape*>::iterator it = _shapeVec->begin() ; it != _shapeVec->end(); ++it){
           switch (_mode[1]) {
             case 1:
                // cout<<(*it)->area()<<endl;
                // cout<<removeAddtionZero(to_string((*it)->area()))<<endl;
                result+=to_string((*it)->area());
                break;
             case 2:
                // cout<<removeAddtionZero(to_string((*it)->perimeter()))<<endl;
                result+=to_string((*it)->perimeter());
                break;
             case 3:
                // cout<<removeAddtionZero(to_string((*it)->sumOfSquares()))<<endl;
                result+=to_string((*it)->sumOfSquares());
                break;
           }
           // cout<<*it<<endl;
           // cout<<*(_shapeVec->end()-1)<<endl;
           if(*it != *(_shapeVec->end()-1) )
            result+=", ";
         }
         return result+="]";
    }
    string removeAddtionZero(string value){
      // cout<<value.size()<<endl;
      for(int i=value.size()-1;i > -1;i--){
        if(value[i]=='0') value.erase(i,1);
        else break;
      }
      return value;

    }
    void ShowList(std::vector<string>* vec){
      for (std::vector<string>::iterator it = vec->begin() ; it != vec->end(); ++it)
        std::cout <<(*it)<<endl;
    }
private:
    string _instruction;
    bool _run=true;
    int _index=0;
    int _count=0;
    std::vector<Shape*>* _shapeVec;

    int _mode[3]={0};//_mode[0]=count,_mode[1]= 0:error     mode[2]= 0:error
                                            // 1:area               1:ascending
                                            // 2:perimeter          2:descending
                                            // 3:sumOfSquares
    bool _isThrow=false;
    string _modeFeature[3]={"area","perimeter","sumOfSquares"};
    string _modeOrder[2]={"inc","dec"};
    char _mark[11]={'!','@','#','$','%','^','&','*','+','>','<'};
    string _shapeName[3]={"^Triangle$","^CircularSector$","^Ellipse$"};
    string _format[3]={"^(Triangle)(\\(-?\\d{1,},-?\\d{1,},-?\\d{1,},-?\\d{1,},-?\\d{1,},-?\\d{1,}\\))$",
                        "^(CircularSector)(\\(-?\\d{1,},-?\\d{1,}\\))$",
                        "^(Ellipse)(\\(-?\\d{1,},-?\\d{1,}\\))$"};
};
