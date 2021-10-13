# MLS Manager
This app is a manager for Mozilla Location Service offline packages for Sailfish OS.


>![](icons/128x128/harbour-mlsmanager.png)


## Mozilla Location Service
This app uses the offline data from [Mozilla Location Service](https://location.services.mozilla.com/). \
The data is licensed under [Public Domain](https://creativecommons.org/publicdomain/zero/1.0/).


## Intention of project
I had alread released some offline packages on [OpenRepos.net](https://openrepos.net/) but I realized keeping all of them up to date will be a very hard job. \
An other problem is the big package sizes, taking away a lot of ressources from OpenRepos.

So I decided to host my own repository with packages and create a manager app. \
And here we are…

All of this is only intended as a temporary solution until Jolla presents an alternative.

## Repository
The repository is available at this address: \
[https://mls-offline-repo.nubecula.org/](https://mls-offline-repo.nubecula.org/)


## Automatic Updates
Updates with actual data will be released weekly (if possible). \
I have created an automatic package creation pipline to make the job a bit easier for me.


## Available Countries
At the moment 185 different countries are available.

## Available Regions
- Africa
- Asia
- Australia and Oceania
- Europe
- North America
- South America

If you need more, let me know.

## How to use

In order to make use of the offline data, the option "High-accuracy positioning" or at least \
"Battery saving mode" must be active in the location settings of Sailfish OS.

## Storage Location

Packages with version >2021.02.10-1 the installation path is in "/home/.system/usr/share/geoclue-provider-mlsdb/". \
So don't worry about size on ROOT partition. Thanks to abranson for his suggestion.

## Translations

- English
- German
- Norwegian Bokmål (by Allan Nordhøy)
- Polish (by atlochowski)
- Slovak (by okruhliak / Ladislav Hodas)
  
If your language is not available you are welcome to support this project by translating it on my self-hosted Weblate server:

[![https://weblate.nubecula.org/engage/harbour-mlsmanager/](https://weblate.nubecula.org/widgets/harbour-mlsmanager/-/multi-auto.svg)](https://weblate.nubecula.org/engage/harbour-mlsmanager/)

## Thanks
I want to thank Petr Tsymbarovich(osetr) for his work on [Storeman](https://openrepos.net/content/osetr/storeman). \
His code helped me to get an idea how to handle repositories.

## Donations

If you like my work, you can buy me a beer! 

[PayPal](https://www.paypal.com/paypalme/nubecula/1) \
[Liberapay](https://liberapay.com/black-sheep-dev/donate)
