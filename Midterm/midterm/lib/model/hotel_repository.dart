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

import 'hotel.dart';

class HotelRepository {
  static List<Hotel> loadProducts(Category category) {
    const allProducts = <Hotel>[
      Hotel(
        category: Category.four,
        id: 'assets/hotel/01.jpg',
        name: 'Hilton Gyeongju',
        location: '484-7 Bomun-ro, Bodeok-dong, Gyeongju-si, Gyeongsangbuk-do',
      ),
      Hotel(
        category: Category.four,
        id: 'assets/hotel/02.jpg',
        name: 'Sheraton Huzhou Hot Spring Resort',
        location: 'China, Zhejiang, Huzhou, Wuxing District, 太湖路5858号 邮政编码: 313006•+86 572 229 9999',
      ),
      Hotel(
        category: Category.four,
        id: 'assets/hotel/03.jpg',
        name: 'The Full Moon Hotel',
        location: '118 Eagle Terrace, Sandgate QLD 4017, Australia',
      ),
      Hotel(
        category: Category.four,
        id: 'assets/hotel/04.jpg',
        name: 'Pangu 7 Star Hotel Beijing',
        location: 'China, Beijing, Chaoyang, 北四环中路27号盘古大观 邮政编码: 100101',
      ),
      Hotel(
        category: Category.five,
        id: 'assets/hotel/05.jpg',
        name: 'Hotel Paradise Busan',
        location: '296 Haeundaehaebyeon-ro, Haeundae-gu, Busan',
      ),
      Hotel(
        category: Category.five,
        id: 'assets/hotel/06.jpg',
        name: 'Town House Galleria',
        location: 'Via Silvio Pellico, 8 20121, Milano',
      ),
      Hotel(
        category: Category.four,
        id: 'assets/hotel/07.jpg',
        name: 'The Westin Josun Seoul',
        location: '106 Sogong-ro, Jung-gu, Seoul',
      ),
      Hotel(
        category: Category.five,
        id: 'assets/hotel/08.jpg',
        name: 'Wanda Reign on the Bund',
        location: 'Huangpu, China, 200120',
      ),
      Hotel(
        category: Category.five,
        id: 'assets/hotel/09.jpg',
        name: 'Emirates Palace',
        location: 'West - Corniche Rd - Abu Dhabi - United Arab Emirates',
      ),
      Hotel(
        category: Category.five,
        id: 'assets/hotel/10.jpg',
        name: 'The Apeiron Island',
        location: 'Dubai',
      ),
      Hotel(
        category: Category.four,
        id: 'assets/hotel/11.jpg',
        name: 'Skybay Hotel Gyeongpo',
        location: '476 Haean-ro, Gangneung-si, Gangwon-do',
      ),
      Hotel(
        category: Category.four,
        id: 'assets/hotel/12.jpg',
        name: 'Seoul Garden Hotel',
        location: '58 Mapo-daero, Mapo-gu, Seoul',
      ),
      Hotel(
        category: Category.four,
        id: 'assets/hotel/13.jpg',
        name: 'Burj Al Arab',
        location: ' شارع جميرا، - Umm Suqeim 3 - Dubai - United Arab Emirates',
      ),
      Hotel(
        category: Category.five,
        id: 'assets/hotel/14.jpg',
        name: 'Marina Bay Sands Singapore',
        location: '10 Bayfront Ave, Singapore 018956',
      ),
      Hotel(
        category: Category.four,
        id: 'assets/hotel/15.jpg',
        name: 'The K Hotel Seoul',
        location: '70 Baumoe-ro 12-gil, Seocho-gu, Seoul',
      ),
      Hotel(
        category: Category.four,
        id: 'assets/hotel/16.jpg',
        name: 'Nest Hotel Incheon',
        location: '19-5 Yeongjonghaeannam-ro, Jung-gu, Incheon',
      ),
      Hotel(
        category: Category.four,
        id: 'assets/hotel/17.jpg',
        name: 'Golden Seoul Hotel',
        location: '663 Gonghang-daero, Gangseo-gu, Seoul',
      ),

    ];
    if (category == Category.all) {
      return allProducts;
    } else {
      return allProducts.where((Hotel p) {
        return p.category == category;
      }).toList();
    }
  }
}
