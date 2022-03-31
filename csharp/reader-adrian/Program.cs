using System;
using System.IO;

namespace reading
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Trying to read the code!");
            Reader test = new Reader("../../../model.ALI");

            // Read the file present in the path
            using (StreamReader sr = new StreamReader("../../../model.ALI"))
            {

                // Iterating the file
                while (sr.Peek() >= 0)
                {

                    // Read the data in the file until the peak

                    // checking if the peak of the char is working
                    bool mal = test.NextElementIsMaterial();
                    bool lig = test.NextElementIsLight();
                    bool mesh = test.NextElementIsMesh();

                  
                    // testing to see if it iis a material and looking at data
                    if (mal)
                    {
                        MaterialData md = test.NextMaterial();
                        Console.WriteLine(md.ToString());
                        Console.WriteLine("name: " + md.name);
                        Console.WriteLine("is T: " + md.isTransparent);
                        Console.WriteLine("red color: " + md.mainColor.r);
                        Console.WriteLine("green color: " + md.mainColor.g);
                        Console.WriteLine("blue color: " + md.mainColor.b);
                        Console.WriteLine("color aph: " + md.mainColor.a);
                        Console.WriteLine(""); //adding spacer

                    }

                    if (lig) {

                        LightData lightData = test.NextLight();
                        Console.WriteLine("light int: " + lightData.intensity) ;
                        Console.WriteLine(""); //adding spacer
                    }
                    if (mesh) {
                        MeshData meshData = test.NextMesh();
                        Console.WriteLine("mesh name: " + meshData.name);

                        Console.WriteLine("meshData.verts - first item: " + meshData.verts[0].ToString());
                        Console.WriteLine("meshData.verts.Count:" + meshData.verts.Count);

                        Console.WriteLine("meshData.uvVerts - first item: " + meshData.uvVerts[0].ToString());
                        Console.WriteLine("meshData.uvVerts.Count: " + meshData.uvVerts.Count);

                        //Console.WriteLine("meshData.uv2Verts - first item: " + meshData.uv2Verts[0].ToString());
                        //Console.WriteLine("meshData.uv2Verts.Count:" + meshData.uv2Verts.Count);

                        Console.WriteLine("submesh name: " + meshData.submeshes[0].materialName);
                        Console.WriteLine("submesh tres list size: " + meshData.submeshes[0].tris.Count);
                        Console.WriteLine("submesh tres - " + meshData.submeshes[0].ToString() );
                        Console.WriteLine("submesh list size: " + meshData.submeshes.Count);

                        //meshData.submeshes.ForEach(p => 

                        //Console.WriteLine(p.materialName),
                        //Console.WriteLine(p.tris)
                        //);


                        Console.WriteLine(""); //adding spacer
                    

                    }

                }
            }




        }
    }
}
