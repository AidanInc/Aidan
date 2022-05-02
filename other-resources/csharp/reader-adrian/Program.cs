using System;
using System.IO;
//using System.Text;

namespace reading
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Trying to read the code!");
            Reader test = new Reader("../../../model.ALI");

            string pathfile = @"../../../outputfile.txt";
            if (!File.Exists(pathfile))
            {
                // Create a file to write to.
                string createText = "Saving output to this file....\n" + Environment.NewLine;
                File.WriteAllText(pathfile, createText);
                //File.AppendAllText(pathfile, appendText + "\n");
            }
            else {
                File.WriteAllText(pathfile, "Saving output to this file...\n"); // the wtrie all test function will clear all that in the file
            }


            // Read the file present in the path
            using (StreamReader sr = new StreamReader("../../../model.ALI"))
            {

                // Iterating the file
                while (sr.Peek() != -1)
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
                        File.AppendAllText(pathfile, md.ToString() + "\n");
                        Console.WriteLine("name: " + md.name);
                        File.AppendAllText(pathfile, "name: " + md.name + "\n");
                        Console.WriteLine("is T: " + md.isTransparent);
                        File.AppendAllText(pathfile, "is T: " + md.isTransparent + "\n");
                        Console.WriteLine("red color: " + md.mainColor.r);
                        File.AppendAllText(pathfile, "red color: " + md.mainColor.r + "\n");
                        Console.WriteLine("green color: " + md.mainColor.g);
                        File.AppendAllText(pathfile, "green color: " + md.mainColor.g + "\n");
                        Console.WriteLine("blue color: " + md.mainColor.b);
                        File.AppendAllText(pathfile, "blue color: " + md.mainColor.b + "\n");
                        Console.WriteLine("color aph: " + md.mainColor.a);
                        File.AppendAllText(pathfile, "color aph: " + md.mainColor.a + "\n");
                        Console.WriteLine(""); //adding spacer
                        File.AppendAllText(pathfile, "" + "\n");

                    }

                    if (lig) {

                        LightData lightData = test.NextLight();
                        Console.WriteLine("light int: " + lightData.intensity) ;
                        File.AppendAllText(pathfile, "light int: " + lightData.intensity + "\n");
                        Console.WriteLine(""); //adding spacer
                        File.AppendAllText(pathfile, "" + "\n");
                    }

                    if (mesh) {
                        MeshData meshData = test.NextMesh();
                        Console.WriteLine("mesh name: " + meshData.name);
                        File.AppendAllText(pathfile, "mesh name: " + meshData.name + "\n");


                        //Console.WriteLine("meshData.verts - first item: " + meshData.verts[0].ToString());
                        Console.WriteLine("meshData.verts list");
                        File.AppendAllText(pathfile, "meshData.verts list" + "\n");
                        meshData.verts.ForEach((v) => Console.WriteLine("verts ---- " + v.ToString()) );
                        meshData.verts.ForEach((v) => File.AppendAllText(pathfile, "verts ---- " + v.ToString() + "\n")  );
                        //Console.WriteLine("meshData.verts.Count:" + meshData.verts.Count);


                        //Console.WriteLine("meshData.uvVerts - first item: " + meshData.uvVerts[0].ToString());
                        Console.WriteLine("meshData.uvVerts list");
                        File.AppendAllText(pathfile, "meshData.uvVerts list" + "\n");
                        meshData.uvVerts.ForEach((v) => Console.WriteLine("uvVerts ---- " + v.ToString()));
                        meshData.uvVerts.ForEach((v) => File.AppendAllText(pathfile, "uvVerts ---- " + v.ToString() + "\n"));
                        //Console.WriteLine("meshData.uvVerts.Count: " + meshData.uvVerts.Count);


                        // this is just 0  - list is empty //  
                        // Console.WriteLine("meshData.uv2Verts - first item: " + meshData.uv2Verts);
                        //Console.WriteLine("meshData.uv2Verts.Count:" + meshData.uv2Verts.Count);


                        for (int i = 0; i < meshData.submeshes.Count; i++) {
                            Console.WriteLine("submesh name " + i + " : " + meshData.submeshes[i].materialName);
                            File.AppendAllText(pathfile, "submesh name " + i + " : " + meshData.submeshes[i].materialName + "\n");


                            meshData.submeshes[i].tris.ForEach((item) => Console.WriteLine( i + " submesh.tris --- " + item ));
                            meshData.submeshes[i].tris.ForEach((item) => File.AppendAllText(pathfile, i + " submesh.tris --- " + item + "\n"));

                        }
                           
                        //Console.WriteLine("submesh list size: " + meshData.submeshes.Count);

                        Console.WriteLine(""); //adding spacer
                        File.AppendAllText(pathfile, "" + "\n");



                    }

                    
                }


                Console.WriteLine(" -- end -- ");
                File.AppendAllText(pathfile, "-- end --" + "\n");
            }
            


        }
    }
}
