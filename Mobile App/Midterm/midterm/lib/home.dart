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
import 'package:intl/intl.dart';
import 'package:url_launcher/url_launcher.dart';

import 'detail.dart';
import 'model/hotel.dart';
import 'model/hotel_repository.dart';

final Uri _url = Uri.parse('https://www.handong.edu/');

const List<Widget> togglebut = <Widget>[
  Icon(Icons.list, size: 20,),
  Icon(Icons.view_column, size: 20,),
];

class HomePage extends StatefulWidget{
  const HomePage({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() => _HomePage();
}

class _HomePage extends State<HomePage> {
  final List<bool> _isSelected = <bool>[false, true];
  ViewType _viewType = ViewType.grid;
  int _crossAxisCount = 2;
  double _aspectRatio = 0.88;

  List<Card> _buildGridCards(BuildContext context) {
    List<Hotel> hotel = HotelRepository.loadProducts(Category.all);

    if (hotel.isEmpty) {
      return const <Card>[];
    }

    final ThemeData theme = Theme.of(context);
    final NumberFormat formatter = NumberFormat.simpleCurrency(
        locale: Localizations.localeOf(context).toString());

    return hotel.map((hotel) {
      return Card(
        elevation: 2.0,
        clipBehavior: Clip.antiAlias,
        // TODO: Adjust card heights (103)
        child: (_viewType == ViewType.list)
        ? Container( // If it is list view
            margin: const EdgeInsets.all(5),
            child: Row(
              children: <Widget>[
                const SizedBox(width: 5,),
                SizedBox(
                  width: 80,
                  height: 70,
                  child: ClipRRect(
                    borderRadius: BorderRadius.circular(4.0),
                    child: Hero(
                      tag: 'hero-${hotel.category}',
                      child: Image.asset(
                        hotel.id,
                        fit: BoxFit.fill,
                      ),
                    ),
                  ),
                ),
                const SizedBox(width: 20,),
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: <Widget>[
                  SizedBox(
                  width: MediaQuery.of(context).size.width - 219,
                  height: 70,
                  child: Column(
                    // TODO: Align labels to the bottom and center (103)
                    crossAxisAlignment: CrossAxisAlignment.start,
                    // TODO: Change innermost Column (103)
                    children: <Widget>[
                      Row(
                        mainAxisSize: MainAxisSize.min,
                        children: List.generate(hotel.star, (int index){
                          return const Icon(
                            Icons.star,
                            size: 10,
                            color: Colors.yellow,
                          );
                        }),
                      ),
                      // TODO: Handle overflowing labels (103)
                      Flexible(
                        child: Text(
                          hotel.name,
                          overflow: TextOverflow.ellipsis,
                          style: const TextStyle(
                            fontSize: 15,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ),
                      const SizedBox(height: 5.0),
                      Flexible(
                        child: Text(
                          hotel.location,
                          overflow: TextOverflow.ellipsis,
                          maxLines: 2,
                          style: const TextStyle(
                            fontSize: 10,
                          ),
                        ),
                      ),
                    ],
                  ),
                  ),
                  ],
                ),
                Align(
                  alignment: Alignment.bottomRight,
                  child: TextButton(
                    style: TextButton.styleFrom(
                      padding: EdgeInsets.all(0),
                      textStyle: TextStyle(fontSize: 15),
                    ),
                    onPressed: (){
                      Navigator.push(
                        context,
                        MaterialPageRoute(
                            builder: (context) => Detail(hotel.category,)
                        ),
                      );
                    },
                    child: Text('more',),
                  ),
                ),
              ],
            ),
        ) :
        Column( // If it is column view
          // TODO: Center items on the card (103)
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            AspectRatio(
              aspectRatio: 18 / 11,
              child:
              ClipRRect(
                borderRadius: BorderRadius.circular(4.0),
                child: Hero(
                  tag: 'hero-${hotel.category}',
                  child: Image.asset(
                    hotel.id,
                    fit: BoxFit.fill,
                  ),
                ),
              ),
            ),
            Expanded(
              child: Padding(
                padding: const EdgeInsets.fromLTRB(7.0, 12.0, 16.0, 8.0),
                child:
                    Stack(
                      //mainAxisSize: MainAxisSize.max,
                      children: <Widget>[
                      const Padding(
                        padding: EdgeInsets.only(right: 5, top: 30,),
                        child: Icon(
                            Icons.place,
                            color: Colors.blue,
                            size: 15,
                        ),
                      ),
                      Container(
                        margin: EdgeInsets.only(left: 20,),
                        width: 130,
                        height: 200,
                        child: Column(
                        // TODO: Align labels to the bottom and center (103)
                        crossAxisAlignment: CrossAxisAlignment.start,
                        // TODO: Change innermost Column (103)
                        children: <Widget>[
                          Row(
                            mainAxisSize: MainAxisSize.min,
                            children: List.generate(hotel.star, (int index){
                                return const Icon(
                                    Icons.star,
                                    size: 10,
                                    color: Colors.yellow,
                                );
                              },
                            ),
                          ),
                          // TODO: Handle overflowing labels (103)
                          Flexible(
                            child: RichText(
                              overflow: TextOverflow.ellipsis,
                              maxLines: 1,
                              strutStyle: const StrutStyle(fontSize: 14),
                              text: TextSpan(
                                  text:hotel.name,
                                  style: const TextStyle(
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold,
                                    fontSize: 12,
                                  ),
                              ),
                            ),
                          ),
                          const SizedBox(height: 3.0),
                          Flexible(
                            child: RichText(
                              overflow: TextOverflow.ellipsis,
                              maxLines: 1,
                              strutStyle: const StrutStyle(fontSize: 8),
                              text: TextSpan(
                                text:hotel.location,
                                style: const TextStyle(
                                  color: Colors.black,
                                  fontSize: 10,
                                ),
                              ),
                            ),
                          ),
                        ],
                      ),
                    ),
                  ],
                ),
              ),
            ),
            Container(
              alignment: Alignment.bottomRight,
              margin: EdgeInsets.only(bottom: 7,),
              height: 20,
              child: TextButton(
                style: TextButton.styleFrom(
                  padding: EdgeInsets.all(0),
                  textStyle: TextStyle(fontSize: 15),
                ),
                  onPressed: (){
                    Navigator.push(
                        context,
                        MaterialPageRoute(
                            builder: (context) => Detail(hotel.category,)
                        ),
                    );
                  },
                child: Text('more',),
              ),
            ),
          ],
        ),
      );
    }).toList();
  }

  // TODO: Add a variable for Category (104)
  @override
  Widget build(BuildContext context) {
    // TODO: Return an AsymmetricView (104)
    // TODO: Pass Category variable to AsymmetricView (104)
    return Scaffold(
      appBar: AppBar(
        title: const Text("Main"),
        centerTitle: true,
        actions: <Widget>[
          IconButton(
            icon: const Icon(
              Icons.search,
              semanticLabel: 'search',
            ),
            onPressed: () {
              Navigator.pushNamed(context, '/search');
            },
          ),
          const IconButton(
            icon: Icon(
              Icons.language,
              semanticLabel: 'filter',
            ),
            onPressed: _launchUrl,
            /*pod error
            * sudo gem install cocoapods
            * sudo gem install ffi
            * cd [project directory]
            * cd ios
            * pod install*/
          ),
        ],
      ),

      body: Column(
          children:<Widget>[
            Container(
              alignment: Alignment.topRight,
              margin: const EdgeInsets.only(top:10, right: 10),
              child:
                ToggleButtons(
                onPressed: (int index) {
                  if(index==0){
                    _crossAxisCount = 1;
                    _aspectRatio = 3.5;
                    _viewType = ViewType.list;
                  }
                  else{
                    _crossAxisCount = 2;
                    _aspectRatio = 0.88;
                    _viewType = ViewType.grid;
                  }
                  // Respond to button selection
                  setState(() {
                    for (int i = 0; i < _isSelected.length; i++) {
                      _isSelected[i] = i == index;
                      }
                    });
                  
                },
                color: Colors.black.withOpacity(0.60),
                selectedColor: Colors.lightBlue,
                selectedBorderColor: Colors.lightBlue,
                fillColor: Colors.lightBlue.withOpacity(0.08),
                splashColor: Colors.lightBlue.withOpacity(0.12),
                hoverColor: Colors.lightBlue.withOpacity(0.04),
                borderRadius: BorderRadius.circular(4.0),
                isSelected: _isSelected,
                children: togglebut,

                constraints: const BoxConstraints(
                  minHeight: 40.0,
                  minWidth: 40.0,
                ),
              ),
            ),
            Expanded(
              child:
                  OrientationBuilder(
                    builder: (context, orientation) {
                    return GridView.count(
                      crossAxisCount: orientation == Orientation.portrait? _crossAxisCount : 3,
                      padding: const EdgeInsets.all(16.0),
                      childAspectRatio: _aspectRatio,
                      children: _buildGridCards(context),
                  );
                }
              ),
            ),
          ],
      ),

      resizeToAvoidBottomInset: false,

      drawer: Drawer(
        child: ListView(
          padding: EdgeInsets.zero,
          children: [
            DrawerHeader(
              child: Stack(
                children: const [
                  Positioned(
                    bottom: 10.0,
                    left: 30.0,
                    child: Text(
                      "Pages",
                      style: TextStyle(color: Colors.white, fontSize: 28),
                    ),
                  )
                ],
              ),
              decoration: const BoxDecoration(
                color: Colors.blue,
              ),
            ),
            ListTile(
              leading: const Icon(Icons.home, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('Home'),
              onTap: () {
                Navigator.pushNamed(context, '/');
              },
            ),
            ListTile(
              leading: const Icon(Icons.search, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('Search'),
              onTap: () {
                Navigator.pushNamed(context, '/search');
              },
            ),
            ListTile(
              leading: const Icon(Icons.location_city, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('Favorite Hotel'),
              onTap: _pushSaved,
            ),
            ListTile(
              leading: const Icon(Icons.person, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('My Page'),
              onTap: () {
                Navigator.pushNamed(context, '/go');
              },
            ),
            ListTile(
              leading: const Icon(Icons.logout, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('Log Out'),
              onTap: () {
                Navigator.pushNamed(context, '/login');
              },
            ),
          ],
        ),
      ),
    );
  }

  void _pushSaved() {
    Navigator.of(context).push(
      MaterialPageRoute<void>(
        builder: (context) {
          final tiles = saved.map(
                (pair) {
              return ListTile(
                title: Text(
                  pair,
                ),
              );
            },
          );
          final divided = tiles.isNotEmpty
              ? ListTile.divideTiles(
            context: context,
            tiles: tiles,
          ).toList()
              : <Widget>[];

          return Scaffold(
            appBar: AppBar(
              title: const Text('Favorite Hotels'),
            ),
            body: //ListView(children: divided),
            ListView.builder(
              itemCount: saved.length,
              itemBuilder: (context, index) {
                final item = saved.elementAt(index);
                final it = saving.elementAt(index);
                return Dismissible(
                  // Each Dismissible must contain a Key. Keys allow Flutter to
                  // uniquely identify widgets.
                  key: Key(item),
                  // Provide a function that tells the app
                  // what to do after an item has been swiped away.
                  onDismissed: (direction) {
                    // Remove the item from the data source.
                    setState(() {
                      saved.remove(item);
                      saving.remove(it);
                    });
                  },
                  // Show a red background as the item is swiped away.
                  background: Container(color: Colors.red),
                  child: Container(
                    margin: const EdgeInsets.only(left: 20, top: 10,),
                    child: ListTile(
                      title: Text(
                        item,
                        style: const TextStyle(
                          fontWeight: FontWeight.bold,
                        ),
                      ),
                    ),
                  ),
                );
              },
            ),
          );
        },
      ),
    );
  }
}

Future<void> _launchUrl() async {
  if (!await launchUrl(_url)) {
    throw 'Could not launch $_url';
  }
}

enum ViewType { grid, list }