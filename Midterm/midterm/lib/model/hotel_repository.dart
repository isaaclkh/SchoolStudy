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
        category: Category.a,
        id: 'assets/hotel/01.jpg',
        name: 'Hilton Gyeongju',
        location: '484-7 Bomun-ro, Bodeok-dong, Gyeongju-si, Gyeongsangbuk-do',
        star: 4,
        telephone: "054-745-7788",
        detail: "Surrounded by scenic countryside next to Lake Bomun, our hotel is less than a kilometer from Gyeongju World Amusement Park. We're nine kilometers from the historic city of Gyeongju, and close to Singyeongju KTX rail station. Enjoy our fitness center, squash court, and indoor and outdoor pools with private cabanas.",
      ),
      Hotel(
        category: Category.b,
        id: 'assets/hotel/02.jpg',
        name: 'Sheraton Huzhou Hot Spring Resort',
        location: 'China, Zhejiang, Huzhou, Wuxing District, 太湖路5858号 邮政编码: 313006•+86 572 229 9999',
        star: 4,
        telephone: "+86 572 229 9999",
        detail: "Find the relaxing vacation experience at Sheraton Huzhou Hot Spring Resort, our revolutionary new hotel in China's scenic Zhejiang Province. Featuring a unique ring-shaped, 27-story structure placed over the waters of Tai Lake, our specially designed hotel boasts an ideal destination near ancient water towns, stone bridges, restored historic districts and waterways fed by the Grand Canal. After exploring the area, discover our hotel's premium amenities, including an onsite day spa, an infinity pool, a private beach and a custom wedding island that extends into Tai Lake. Experience beautiful water views as you sip on handcrafted cocktails or enjoy a leisurely meal in one of our waterfront restaurants. Unpack in elegant rooms with sleek marble bathrooms and complimentary Wi-Fi. If visiting for event planning reasons, take advantage of our spacious Grand Ballroom and state-of-the-art meeting facilities. Whatever your reason for visiting, we look forward to welcoming you at Sheraton Huzhou Hot Spring Resort.",
      ),
      Hotel(
        category: Category.c,
        id: 'assets/hotel/03.jpg',
        name: 'The Full Moon Hotel',
        location: '118 Eagle Terrace, Sandgate QLD 4017, Australia',
        star: 4,
        telephone: " ",
        detail: " ",
      ),
      Hotel(
        category: Category.d,
        id: 'assets/hotel/04.jpg',
        name: 'Pangu 7 Star Hotel Beijing',
        location: 'China, Beijing, Chaoyang, 北四环中路27号盘古大观 邮政编码: 100101',
        star: 4,
        telephone: "+86 10 5906 7777",
        detail: "This lavish hotel is 4 km from the China Science and Technology Museum, and 3 km from both Beijing Olympic Park and live events at the National Stadium. Sophisticated rooms and suites feature free Wi-Fi, flat-screen TVs and fireplaces, as well as minibars and marble bathrooms. Some offer butler service, sitting areas, whirlpool tubs and/or balconies. Dining options consist of 3 restaurants, a cocktail lounge with a terrace, and a formal cafe/bar with regular live music. Other amenities include an indoor pool, a gym, and meeting and event space. Breakfast is available.",
      ),
      Hotel(
        category: Category.e,
        id: 'assets/hotel/05.jpg',
        name: 'Hotel Paradise Busan',
        location: '296 Haeundaehaebyeon-ro, Haeundae-gu, Busan',
        star: 5,
        telephone: "051-742-2121",
        detail: "On lively Haeundae Beach, this upscale hotel is 7 minutes' walk from Sea Life Busan Aquarium. Chic, understated rooms come with flat-screens. Features in some rooms include beach views, sofabeds and quilted headboards. Suites add living rooms, and upgraded suites have dining areas and balconies. Club rooms include access to a private lounge with free breakfast.Dining options include Japanese, Chinese and European-style restaurants, as well as an airy lobby lounge, and a British-style pub with live entertainment. There's also a casino, and an infinity pool overlooking the sea, as well as a sauna, a fitness room and a kids' playroom.",
      ),
      Hotel(
        category: Category.f,
        id: 'assets/hotel/06.jpg',
        name: 'Town House Galleria',
        location: 'Via Silvio Pellico, 8 20121, Milano',
        star: 5,
        telephone: "+39 02 8845 5555",
        detail: "The hotel is located in the historical center of Milan and housed within the Galleria Vittorio Emanuele II. Originally designed in 1861 by Giuseppe Mengoni and built between 1865 and 1877, the Galleria is named after the first King of Italy, Vittorio Emanuele II. The five-story structure features two-glass vaulted arcades and a massive central dome connecting the Piazza del Duomo to Piazza della Scala.",
      ),
      Hotel(
        category: Category.g,
        id: 'assets/hotel/07.jpg',
        name: 'The Westin Josun Seoul',
        location: '106 Sogong-ro, Jung-gu, Seoul',
        star: 4,
        telephone: "02-771-0500",
        detail: "In a bustling downtown area, this upscale hotel fronted with a colorful pagoda is a 4-minute walk from a metro station, and a 17-minute subway trip from Gyeongbokgung, a 14th-century royal palace. Refined rooms have city views, complimentary Wi-Fi and flat-screen TVs. Suites add living areas, and some provide separate living rooms. Room service is offered. Parking is free. There are 5 posh restaurants, including Cantonese and Italian eateries, as well as an elegant lobby bar. Other amenities include an indoor pool, a sauna, and a sleek gym with floor-to-ceiling windows. There's also a business center.",
      ),
      Hotel(
        category: Category.h,
        id: 'assets/hotel/08.jpg',
        name: 'Wanda Reign on the Bund',
        location: 'Huangpu, China, 200120',
        star: 5,
        telephone: "+86 21 5368 8888",
        detail: "Located in the heart of Shanghai, Wanda Reign on the Bund features spectacular views of the Bund, Huangpu River and Pudong skyline. It boasts extravagance and high-tech amenities, a diversity of fine dining options in a luxurious setting, and crafted hospitality. Free WiFi is offered throughout the property. Guests can conveniently walk to the hotel’s historic neighbours, the ancient Yu Garden and City God Temple. The hotel is 42 km from Shanghai Pudong International Airport, 16 km from Shanghai Hongqiao Airport, and 6.4 km from Shanghai Railway Station. With the Art Deco-inspired interiors, the hotel integrates architecture of different cultures and classical arts of Shanghai. Ranging from 45 square metres to 288 square metres, all these 190 luxurious rooms have a flat-screen TV with satellite channels. Certain units include a seating area to relax after a busy day. Guests can enjoy a cup of tea while looking out at the sea or garden. Extras include slippers and free toiletries. The sophisticated design seamlessly integrates with breathtaking views of The Bund, Huangpu River, Pudong skyline and Yu Garden.",
      ),
      Hotel(
        category: Category.i,
        id: 'assets/hotel/09.jpg',
        name: 'Emirates Palace',
        location: 'West - Corniche Rd - Abu Dhabi - United Arab Emirates',
        star: 5,
        telephone: "+971 2 690 9000",
        detail: "Set on 85 hectares of landscaped gardens, this palatial beachfront hotel is 4 km from both the Marina Mall and the Qasr al-Hosn fort. The opulent rooms feature balconies with garden, pool or gulf views. All provide free Wi-Fi and flat-screen TVs. Suites add living rooms and whirlpool tubs. Room and butler service are offered. There are 14 restaurants and bars, including a romantic BBQ eatery on the beach. Other amenities include adventure and leisure pools, a kids' club, and jogging and cycling trails, plus a spa and 2 fitness centres. The hotel has a private beach and a marina. Bike rentals, yoga sessions and camel rides are available.",
      ),
      Hotel(
        category: Category.j,
        id: 'assets/hotel/10.jpg',
        name: 'The Apeiron Island',
        location: 'Dubai',
        star: 5,
        telephone: "698 806 0283",
        detail: "Apeiron Hotel is a design concept for a new 7 star hotel in Dubai. Developer and construction schedule have not been announced as of October 2007. The Apeiron Hotel would be the second 7 star hotel to be built in Dubai (The Burj Al Arab hotel was the first 7 star hotel). Designed by UKâ€™s Sybarite Architects, the hi-tech futuristic hotel would feature a two-storeyed jungle at the top of the 28-storeyed building. The seven star hotel is an US 350 million dollars project that would be 300m from the coast of Dubai. Access to the hotel is restricted to water and air only.",
      ),
      Hotel(
        category: Category.k,
        id: 'assets/hotel/11.jpg',
        name: 'Skybay Hotel Gyeongpo',
        location: '476 Haean-ro, Gangneung-si, Gangwon-do',
        star: 4,
        telephone: "033-923-2000",
        detail: "Set in a modern building with views of the sea, this upscale hotel is 6 minutes by bus from Gyeongpo Beach and a 2-minute walk from a bus stop. The bright rooms feature flat-screen TVs. Some rooms add minifridges and sitting areas. Breakfast is available. There are 2 restaurants, plus a bar and event space. Other amenities include an outdoor infinity pool, an indoor pool and a gym, in addition to a spa offering saunas, steam rooms and massage services.",
      ),
      Hotel(
        category: Category.l,
        id: 'assets/hotel/12.jpg',
        name: 'Seoul Garden Hotel',
        location: '58 Mapo-daero, Mapo-gu, Seoul',
        star: 4,
        telephone: "02-710-7111",
        detail: "In a modern building next to a metro station, this polished hotel is a 22-minute metro ride from both Gyeongbokgung palace and Dongdaemun Market. Featuring chic, understated decor, the laid-back rooms come with free Wi-Fi and flat-screen TVs, plus minibars, and tea and coffeemaking facilities. Some have terraces. Suites add living rooms, and some come with dining rooms. Room service is offered. Parking is free. Breakfast is offered in an airy Italian restaurant, and there's also a sushi eatery and a cafe/bar. Other amenities include a fitness room and a business center. There are also meeting rooms, a ballroom and event spaces.",
      ),
      Hotel(
        category: Category.m,
        id: 'assets/hotel/13.jpg',
        name: 'Burj Al Arab',
        location: ' شارع جميرا، - Umm Suqeim 3 - Dubai - United Arab Emirates',
        star: 4,
        telephone: " ",
        detail: " ",
      ),
      Hotel(
        category: Category.n,
        id: 'assets/hotel/14.jpg',
        name: 'Marina Bay Sands Singapore',
        location: '10 Bayfront Ave, Singapore 018956',
        star: 5,
        telephone: "+971 4 301 7777",
        detail: "Set on an island in a striking sail-shaped building, this luxury hotel is a 5-minute walk from Wild Wadi Water Park and 4 km from Mall of the Emirates. Opulent suites feature floor-to-ceiling windows with gulf or city views. All have 24-carat gold iPads, free Wi-Fi, flat-screen TVs and iPods. They offer Egyptian linens, designer toiletries, whirlpool baths and butler service. Upgraded suites include snooker tables, libraries, cinemas and private elevators. A breakfast buffet, parking, and water park passes are free. Amenities also include 9 restaurants and bars, 4 pools and a private beach. There's a spa, a gym, a helipad and a kids' club.",
      ),
      Hotel(
        category: Category.o,
        id: 'assets/hotel/15.jpg',
        name: 'The K Hotel Seoul',
        location: '70 Baumoe-ro 12-gil, Seocho-gu, Seoul',
        star: 4,
        telephone: " ",
        detail: " ",
      ),
      Hotel(
        category: Category.p,
        id: 'assets/hotel/16.jpg',
        name: 'Nest Hotel Incheon',
        location: '19-5 Yeongjonghaeannam-ro, Jung-gu, Incheon',
        star: 4,
        telephone: "032-743-9000",
        detail: "On the waterfront overlooking the Yellow Sea, this polished hotel is a 4-minute walk from Yongyu train station and a 38-minute bus trip from Incheon International Airport. The straightforward rooms have flat-screen TVs, free Wi-Fi and minibars, plus Bluetooth speakers, and tea and coffeemaking equipment; some offer sea views. Suites add separate sitting areas. Room service is available. There's a complimentary airport shuttle. There are 2 restaurants. A breakfast buffet is extra. Other amenities include 2 bars and meeting space, along with a fitness room and a spa. A playground, a playroom and outdoor pools are provided.",
      ),
      Hotel(
        category: Category.q,
        id: 'assets/hotel/17.jpg',
        name: 'Golden Seoul Hotel',
        location: '663 Gonghang-daero, Gangseo-gu, Seoul',
        star: 4,
        telephone: "02-3397-2000",
        detail: "This modern business hotel in the suburban Gangseo-gu district is a 4-minute walk from a subway station and 60 minutes by bus to the 14th-century Gyeongbokgung Palace. Contemporary rooms feature neutral decor and come with flat-screen TVs and free Wi-Fi. They also include minifridges and tea and coffeemaking facilities. Some rooms add views of the Han River. Breakfast is available (charge). There's a bright restaurant with a terrace, along with a cafe. The rooftop lounge features views of the Han River. Other amenities include meeting/event rooms, a fitness room and laundry facilities (fee).",
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
