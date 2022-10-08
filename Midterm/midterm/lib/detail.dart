// Copyright 2018-present the Flutter authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import 'package:flutter/material.dart';
import '../model/hotel.dart';
import '../model/hotel_repository.dart';

final saved = <String>{};
final saving = <Hotel>{};

class Detail extends StatefulWidget{
  final Category category;
  const Detail(this.category, {Key? key,}) : super(key: key);

  @override
  State<StatefulWidget> createState() => _Detail();
}

class _Detail extends State <Detail>{
  //List<Hotel> hotel = HotelRepository.loadProducts(Category.a);
  Category get cat => widget.category;
  List<Hotel> hotels = HotelRepository.loadProducts(Category.all);

  @override
  Widget build(BuildContext context) {
    List<Hotel> hotel = HotelRepository.loadProducts(cat);
    Hotel chose = hotel[0];

    final alreadySaved = saved.contains(chose.name);

    // TODO: implement build
    Widget titleSection = Container(
      padding: const EdgeInsets.only(left: 32, bottom: 10),
      child: Row(
        children: [
          Expanded(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Container(
                  padding: const EdgeInsets.only(bottom: 20, top: 20),
                  child: Row(
                    mainAxisSize: MainAxisSize.min,
                    children: List.generate(4, (int index){
                      return const Icon(
                        Icons.star,
                        size: 30,
                        color: Colors.yellow,
                      );
                    }),
                  ),
                ),
                Padding(
                  padding: const EdgeInsets.only(right: 32,),
                  child: Text(
                    chose.name,
                    style: const TextStyle(
                      fontWeight: FontWeight.bold,
                      color: Colors.indigo,
                      fontSize: 20,
                    ),
                  ),
                ),
              ],
            ),
          ),
        ],
      ),
    );

    Color color = Theme.of(context).primaryColor;

    Widget buttonSection = Container(
      padding: const EdgeInsets.only(left: 32),
      child: Column(
        mainAxisAlignment: MainAxisAlignment.start,
        children: [
          _buildInformationArea(color, Icons.location_on, chose.location),
          const SizedBox(height: 10,),
          _buildInformationArea(color, Icons.phone, chose.telephone),
          const SizedBox(height: 10,),
        ],
      ),
    );

    Widget textSection = Padding(
      padding: const EdgeInsets.only(left: 32, top: 10, right: 32,),
      child: Text(
        chose.detail,
        softWrap: true,
        style: const TextStyle(
          color: Colors.lightBlue,
        ),
      ),
    );

    return Scaffold(
        appBar: AppBar(
          title: const Text('Detail'),
        ),
        body: ListView(
          children: [
            Stack(
              children: <Widget>[
                Hero(
                  tag: 'hero-${chose.category}',
                  child: Card(
                    margin: EdgeInsets.zero,
                    child: InkWell(
                      onDoubleTap: (){
                        setState(() {
                          if(alreadySaved){
                            saved.remove(chose.name);
                            saving.remove(chose);
                          }
                          else{
                            saved.add(chose.name);
                            saving.add(chose);
                          }
                        });
                      },
                      child: Image.asset(
                        chose.id,
                        width: 600,
                        height: 240,
                        fit: BoxFit.cover,
                      ),
                    ),
                  ),
                ),
                Container(
                  alignment: Alignment.topRight,
                  padding: const EdgeInsets.all(10),
                  child: Icon(
                    alreadySaved? Icons.favorite : Icons.favorite_border,
                    color: alreadySaved? Colors.red : null,
                  ),
                ),
              ],
            ),
            titleSection,
            buttonSection,
            const Divider(
              thickness: 1,
              color: Colors.grey,
              indent: 30,
              endIndent: 30,
            ),
            textSection,
          ],
        ),
    );
  }

  Row _buildInformationArea(Color color, IconData icon, String label){
    return Row(
      mainAxisAlignment: MainAxisAlignment.start,
      children: <Widget>[
        Container(
          padding: const EdgeInsets.only(right: 5),
            child: Icon(
              icon,
              color: color,
              size: 25,
            ),
        ),
        Expanded(
          child: Padding(
            padding: const EdgeInsets.only(right: 32,),
            child: Text(
              label,
              style: const TextStyle(
                color: Colors.lightBlue,
                fontSize: 14,
              ),
            ),
          ),
        ),
      ],
    );
  }
}
