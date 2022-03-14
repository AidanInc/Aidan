// See https://aka.ms/new-console-template for more information

var reader = new Reader(@"C:\Users\malik\OneDrive\Desktop\app\model.ali");



// Review how to advance a binary reader.
//reader.NextLight();
//reader.NextMaterial();

while (true){
   
    if(reader.NextElementIsMesh()){
        var meshData = reader.NextMesh();
       // Console.WriteLine(meshData.ToString());
        continue;
    }
    if(reader.NextElementIsMaterial()){
        var MaterialData=reader.NextMaterial();
        Console.WriteLine(MaterialData.ToString());
        continue;
    }
    if(reader.NextElementIsLight()){
        reader.NextLight();
        var lightData = reader.NextLight();
        Console.WriteLine(lightData.ToString());
        
        continue;
    }
    else{
        break;
    }
    
}
//Console.WriteLine(Reader.NextMaterial());

