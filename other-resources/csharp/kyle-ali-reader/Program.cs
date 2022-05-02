using System;
using System.IO;

namespace reading
{
    class Program
    {
        static void Main(string[] args)
        {
            //init reader
            Reader test = new Reader("../../../model.ALI");

            //read ali file
            using (StreamReader sr = new StreamReader("../../../model.ALI"))
            {

                //iterate until end of file
                while (sr.Peek() >= 0)
                {

                    // if mat print mat data
                    if (test.NextElementIsMaterial())
                    {
                        MaterialData md = test.NextMaterial();
                        Console.WriteLine(md.ToString());
                        Console.WriteLine("name: " + md.name);
                        Console.WriteLine("Transparency: " + md.isTransparent);
                        Console.WriteLine("red val: " + md.mainColor.r);
                        Console.WriteLine("green val: " + md.mainColor.g);
                        Console.WriteLine("blue val: " + md.mainColor.b);
                        Console.WriteLine("alpha val: " + md.mainColor.a);
                        Console.WriteLine(""); 

                    }

                    //if light print light data
                    if (test.NextElementIsLight())
                    {

                        LightData lightData = test.NextLight();
                        Console.WriteLine("light int: " + lightData.intensity);
                        Console.WriteLine(""); 
                    }

                    //if mesh print mesh data
                    if (test.NextElementIsMesh())
                    {
                        MeshData meshData = test.NextMesh();
                        Console.WriteLine("mesh name: " + meshData.name);

                        meshData.submeshes.ForEach(p => Console.WriteLine(p.materialName));
                        Console.WriteLine(""); 


                    }

                }
            }




        }
    }
}

