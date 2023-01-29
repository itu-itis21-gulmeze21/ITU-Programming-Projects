import sqlite3 as dbapi2
from flask import Flask, render_template, request

app=Flask(__name__)


def home_page():
    if request.method == "POST":
        with dbapi2.connect('sqlitedb.db') as connection:
            cursor = connection.cursor()
            query = """DROP TABLE Fantasy_team"""
            cursor.execute(query)
            return render_template("home_page.html")
    return render_template("home_page.html")
app.add_url_rule("/", view_func=home_page,methods=['GET','POST'])

def teams():
    euro_teams = getTeams()
    return render_template("teams.html", euro_teams=euro_teams)
app.add_url_rule("/teams", view_func=teams)

def team_stats(team):
    squad = getSquad(team)
    scorers = getMostGoals(team)
    assisters = getMostAssists(team)
    saves = getMostSaves(team)
    attempts = getMostAttempts(team)
    tackles = getMostTackles(team)
    return render_template("team_stats.html",team=team,squad=squad,scorers=scorers, assisters=assisters,saves=saves,attempts=attempts,tackles=tackles )
app.add_url_rule("/team_stats/<team>", view_func=team_stats)

def all_games():
    games = getAllGames()
    return render_template("all_games.html", games=games)
app.add_url_rule("/all_games", view_func=all_games)

def stats():
    goal=getMostGoalsGeneral()
    assist=getMostAssistsGeneral()
    pas=getMostPassesGeneral()
    yellow=getMostYellowGeneral()
    save=getMostSavesGeneral()
    tackle = getMostTacklesGeneral()
    goalranking = getPowerRankingTeams('Goals')
    assistranking = getPowerRankingTeams('Assists')
    tackleranking = getPowerRankingTeams('Tackles')
    recoverranking = getPowerRankingTeams('Recovered balls')
    savesranking = getPowerRankingTeams('Saves')
    passaccuracyranking = getPowerRankingTeamsAvg('Passes accuracy')
    possessionranking = getPowerRankingTeamsAvg('Ball Possession')
    return render_template("stats.html",goal=goal,assist=assist,pas=pas,yellow=yellow,save=save,tackle=tackle,goalranking=goalranking,assistranking=assistranking,tackleranking=tackleranking,recoverranking=recoverranking,savesranking=savesranking,passaccuracyranking=passaccuracyranking,possessionranking=possessionranking)
app.add_url_rule("/stats",view_func=stats)

def randomfacts():
    mostdistancecoveredgame = getRandomStats('Distance covered (Km)')
    mostcorner = getRandomStats('Corners')
    mostfoulscommitted = getRandomStats('Fouls committed')
    mostgoalsscored = getRandomStats('Goals')
    mostgoalsconceded = getRandomStats('Goals conceded')
    mostpassacc = getRandomStats('Passes accuracy')
    redcardref = getRefCards('Red cards')
    yellowcardref = getRefCards('Yellow cards')
    return render_template("randomfacts.html",mostdistancecoveredgame=mostdistancecoveredgame,mostcorner=mostcorner,mostfoulscommitted=mostfoulscommitted,mostgoalsscored=mostgoalsscored,mostgoalsconceded=mostgoalsconceded,mostpassacc=mostpassacc,redcardref=redcardref,yellowcardref=yellowcardref)
app.add_url_rule("/randomfacts",view_func=randomfacts)


def fantasyEuro2020():
    return render_template("fantasyEuro2020.html")
app.add_url_rule("/fantasyEuro2020",view_func=fantasyEuro2020)

def update():
    euro_teams = getTeams()
    team = request.form.get("team")
    squad = getSquad(team)

    if request.method == "POST":
        # getting input with name = fname in HTML form
        first_name = request.form.get("fname")
        # getting input with name = lname in HTML form
        last_name = request.form.get("lname")
        desired_value = request.form.get("dvalue")
        attribute = request.form.get("attribute")
        euro_teams = getTeams()
        with dbapi2.connect('sqlitedb.db', timeout=10) as connection:
            cursor = connection.cursor()
            query = """update Match_lineups set '%s' = '%s' where (OfficialName= '%s') and (OfficialSurname = '%s')""" %(attribute,desired_value,first_name,last_name)
            cursor.execute(query)
        if attribute == "OfficialSurname":
            with dbapi2.connect('sqlitedb.db', timeout=10) as connection:
                cursor = connection.cursor()
                query = """update Match_player_statistics set PlayerSurname = '%s' where (PlayerName= '%s') and (PlayerSurname = '%s')""" %(desired_value,first_name,last_name)
                cursor.execute(query)
        return render_template("updated.html",euro_teams=euro_teams,squad=squad,attribute=attribute,desired_value=desired_value)
    return render_template("update.html",euro_teams=euro_teams,squad=squad)
app.add_url_rule("/update",view_func=update,methods=['GET','POST'])

def updateStats():
    games = getAllGames()
    statistics = getPlayerStatName()
    if request.method == "POST":
        first_name = request.form.get("fname")
        last_name = request.form.get("lname")
        match_id = request.form.get("game")
        stat = request.form.get("stat")
        value = request.form.get("value")
        player_id = getPlayerID(first_name, last_name)
        stat_id = getPlayerStatID(stat)
        with dbapi2.connect('sqlitedb.db') as connection:
            cursor = connection.cursor()
            query = """update Match_player_statistics set rank='%d' where (MatchID='%s') and (PlayerID='%d') and (StatsID = '%d')""" %(int(value),match_id,player_id[0],int(stat_id[0]))
            cursor.execute(query)
        return render_template("updateStats.html",games=games,statistics=statistics)
    return render_template("updateStats.html",games=games,statistics=statistics)
app.add_url_rule("/updateStats",view_func=updateStats,methods=['GET','POST'])


def release():
    euro_teams = getTeams()
    team = request.form.get("Team")
    squad=getSquad(team)
    if request.method == "POST":

        surname=request.form.get("last_name")
        euro_teams=getTeams()
        with dbapi2.connect('sqlitedb.db',timeout=10) as connection:
            cursor=connection.cursor()
            query="""DELETE FROM Match_lineups where  (OfficialSurname = '%s')"""%surname
            cursor.execute(query)
        return render_template("released.html",euro_teams=euro_teams,squad=squad,surname=surname)
    return render_template("release.html",euro_teams=euro_teams,squad=squad)
app.add_url_rule("/release",view_func=release,methods=['GET','POST'])


def fantasy_draft():
    goalkeepers = getGoalkeepers()
    defenders = getDefenders()
    midfielders = getMidfielders()
    forwards = getForwards()
    players = []

    if request.method == "POST":

        players.append(request.form.get("goalkeeper"))
        players.append(request.form.get("defenders1"))
        players.append(request.form.get("defenders2"))
        players.append(request.form.get("defenders3"))
        players.append(request.form.get("defenders4"))
        players.append(request.form.get("midfielders1"))
        players.append(request.form.get("midfielders2"))
        players.append(request.form.get("midfielders3"))
        players.append(request.form.get("forwards1"))
        players.append(request.form.get("forwards2"))
        players.append(request.form.get("forwards3"))
        with dbapi2.connect('sqlitedb.db') as connection:
            cursor = connection.cursor()
            query = """create table Fantasy_team (PlayerSurname varchar(80) primary key)"""
            cursor.execute(query)
        with dbapi2.connect('sqlitedb.db') as connection:
            cursor = connection.cursor()
            for item in players:
                query = """insert into Fantasy_team values('%s')"""% item
                cursor.execute(query)
        goals = statsFantasy("Goals")
        assists = statsFantasy("Assists")
        saves = statsFantasy("Saves")
        redCards = statsFantasy("Red cards")
        yellowCards = statsFantasy("Yellow cards")
        attempts = statsFantasy("Total Attempts")
        passes = statsFantasy("Passes completed")
        return render_template("fantasy_draft_completed.html", goalkeepers=goalkeepers, defenders=defenders, midfielders=midfielders, forwards=forwards,players=players,goals=goals,assists=assists,saves=saves,redCards=redCards,yellowCards=yellowCards,attempts=attempts,passes=passes)
    return render_template("fantasy_draft.html",goalkeepers=goalkeepers,defenders=defenders,midfielders=midfielders,forwards=forwards)
app.add_url_rule("/fantasy_draft",view_func=fantasy_draft,methods=['GET','POST'])

def insertPlayer():
    games = getAllGames()
    countries = getTeams()
    if request.method == "POST":
        first_name = request.form.get("fname")
        last_name = request.form.get("lname")
        match_id = request.form.get("game")
        countrySelected = request.form.get("teamselect")
        player_id = getPlayerID(first_name,last_name)
        attributes = getPlayerAttributes(player_id)
        teamsSelected = getTeamsByID(int(match_id))

        with dbapi2.connect('sqlitedb.db') as connection:
            cursor = connection.cursor()
            query = """insert into Match_lineups values('%s','%s','%s','True','False','False','%s','%d','%s','%s','%s','%s','%s','%s','%s','False',0,0,0,'NA')"""% (match_id,teamsSelected[0][0],teamsSelected[0][1],countrySelected,player_id[0],first_name,last_name,attributes[0][0],attributes[0][1],attributes[0][2],attributes[0][3],attributes[0][4])
            cursor.execute(query)
        return render_template("insertPlayer.html",games=games,countries=countries)
    return render_template("insertPlayer.html",games=games,countries=countries)
app.add_url_rule("/insertPlayer",view_func=insertPlayer,methods=['GET','POST'])

def deletePlayer():
    games = getAllGames()
    if request.method == "POST":
        first_name = request.form.get("fname")
        last_name = request.form.get("lname")
        match_id = request.form.get("game")
        player_id = getPlayerID(first_name, last_name)
        with dbapi2.connect('sqlitedb.db') as connection:
            cursor = connection.cursor()
            query = """delete from Match_lineups where (MatchID='%s') and (ID='%d')""" % (match_id,player_id[0])
            cursor.execute(query)
        return render_template("deletePlayer.html",games=games)
    return render_template("deletePlayer.html",games=games)
app.add_url_rule("/deletePlayer",view_func=deletePlayer,methods=['GET','POST'])

def insertPlayerStats():
    games = getAllGames()
    countries = getTeams()
    statistics = getPlayerStatName()
    if request.method == "POST":
        first_name = request.form.get("fname")
        last_name = request.form.get("lname")
        match_id = request.form.get("game")
        stat = request.form.get("stat")
        value = request.form.get("value")
        player_id = getPlayerID(first_name,last_name)
        teamsSelected = getTeamsByID(int(match_id))
        stat_id= getPlayerStatID(stat)
        print(stat_id)
        with dbapi2.connect('sqlitedb.db') as connection:
            cursor = connection.cursor()
            query = """insert into Match_player_statistics values('%s','%s','%s','%d','%s','%s','False',0,'%d','%s','%s',0)"""% (match_id,teamsSelected[0][0],teamsSelected[0][1],player_id[0],first_name,last_name,int(stat_id[0]),stat,value)
            cursor.execute(query)
        return render_template("insertPlayerStats.html",games=games,countries=countries,statistics=statistics)
    return render_template("insertPlayerStats.html",games=games,countries=countries,statistics=statistics)
app.add_url_rule("/insertPlayerStats",view_func=insertPlayerStats,methods=['GET','POST'])

def deletePlayerStats():
    games = getAllGames()
    statistics = getPlayerStatName()
    if request.method == "POST":
        first_name = request.form.get("fname")
        last_name = request.form.get("lname")
        match_id = request.form.get("game")
        stat = request.form.get("stat")
        stat_id = getPlayerStatID(stat)
        player_id = getPlayerID(first_name, last_name)
        with dbapi2.connect('sqlitedb.db') as connection:
            cursor = connection.cursor()
            query = """delete from Match_player_statistics where (MatchID='%s') and (PlayerID='%d') and (StatsID='%d')""" % (match_id,player_id[0],int(stat_id[0]))
            cursor.execute(query)
        return render_template("deletePlayerStats.html",games=games,statistics=statistics)
    return render_template("deletePlayerStats.html",games=games,statistics=statistics)
app.add_url_rule("/deletePlayerStats",view_func=deletePlayerStats,methods=['GET','POST'])

def getPlayerStatName():
    stat=[]
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """SELECT DISTINCT Value from Match_player_statistics"""
        cursor.execute(query)
    for item in cursor:
        item = str(item).strip("('',)")
        stat.append(item)
    return stat
def getPlayerStatID(stat):
    statid=[]
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """SELECT DISTINCT StatsID from Match_player_statistics where value = '%s'"""%stat
        cursor.execute(query)
    for item in cursor:
        item = str(item).strip("(,)")
        statid.append(item)
    return statid

def getPlayerID(name,surname):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select distinct ID from Match_lineups where (OfficialName='%s') and (OfficialSurname='%s')""" % (name, surname)
        cursor.execute(query)
        player_id = cursor.fetchone()
    return player_id

def getPlayerAttributes(id):
    attributes = []
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select distinct ShortName,Role,JerseyNumber,IsGoalkeeper,JerseyName from Match_lineups where ID='%d' """ % id
        cursor.execute(query)
    for item in cursor:

        attributes.append(item)
    return attributes

def getTeamsByID(id):
    teams = []
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select distinct HomeTeam,AwayTeam from Match_lineups where MatchID='%d' """ % id
        cursor.execute(query)
    for item in cursor:

        teams.append(item)
    return teams


def getTeams():
    euro_teams = []
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = "SELECT DISTINCT HomeTeamName FROM Match_information ORDER BY HomeTeamName"
        cursor.execute(query)
    for item in cursor:
        item = str(item).strip("('',)")
        euro_teams.append(item)
    return euro_teams

def getAllGames():
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = "SELECT HomeTeamName, AwayTeamName,ScoreHome,ScoreAway,RoundName,MatchID FROM Match_information"
        cursor.execute(query)
        games = cursor.fetchall()
    return games

def getSquad(team):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select distinct OfficialName,OfficialSurname,JerseyNumber,Role from Match_lineups where (Country='%s') and (JerseyNumber <> 'None')""" %team
        cursor.execute(query)
        squad = cursor.fetchall()
    return squad

def getGoalkeepers():
    goalkeepers = []
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select distinct OfficialSurname from Match_lineups where (Role='goalkeepers') """
        cursor.execute(query)
    for item in cursor:
        item = str(item).strip("('',)")
        goalkeepers.append(item)
    return goalkeepers

def getDefenders():
    defenders = []
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select distinct OfficialSurname from Match_lineups where (Role='defenders') """
        cursor.execute(query)
    for item in cursor:
        item = str(item).strip("('',)")
        defenders.append(item)
    return defenders
def getMidfielders():
    midfielders = []
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select distinct OfficialSurname from Match_lineups where (Role='midfielders') """
        cursor.execute(query)
    for item in cursor:
        item = str(item).strip("('',)")
        midfielders.append(item)
    return midfielders
def getForwards():
    forwards = []
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select distinct OfficialSurname from Match_lineups where (Role='forwards') """
        cursor.execute(query)
    for item in cursor:
        item = str(item).strip("('',)")
        forwards.append(item)
    return forwards




def getPowerRankingTeams(stat):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """SELECT TeamName,SUM(Value) from Match_team_statistics where (StatsName = '%s') group by TeamName order by SUM(Value) desc"""%stat
        cursor.execute(query)
        power_ranking = cursor.fetchall()
    return power_ranking
def getPowerRankingTeamsAvg(stat):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """SELECT TeamName,AVG(Value) from Match_team_statistics where (StatsName = '%s') group by TeamName order by AVG(Value) desc"""%stat
        cursor.execute(query)
        power_ranking = cursor.fetchall()
    return power_ranking
def getMostGoals(team):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select PlayerSurname,sum(Value) from Match_player_statistics,Match_lineups where (Match_player_statistics.MatchID=Match_lineups.MatchID) and (Match_player_statistics.PlayerID=Match_lineups.ID) and (Match_lineups.Country='%s') and (Match_player_statistics.StatsName='Goals') group by(Match_lineups.ID) order by sum(Value) desc""" %team
        cursor.execute(query)
        scorers = cursor.fetchall()
    return scorers

def getMostAssists(team):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select PlayerSurname,sum(Value) from Match_player_statistics,Match_lineups where (Match_player_statistics.MatchID=Match_lineups.MatchID) and (Match_player_statistics.PlayerID=Match_lineups.ID) and (Match_lineups.Country='%s') and (Match_player_statistics.StatsName='Assists') group by(Match_lineups.ID) order by sum(Value) desc""" %team
        cursor.execute(query)
        assisters = cursor.fetchall()
    return assisters

def getMostSaves(team):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select PlayerSurname,sum(Value) from Match_player_statistics,Match_lineups where (Match_player_statistics.MatchID=Match_lineups.MatchID) and (Match_player_statistics.PlayerID=Match_lineups.ID) and (Match_lineups.Country='%s') and (Match_player_statistics.StatsName='Saves') group by(Match_lineups.ID) order by sum(Value) desc""" %team
        cursor.execute(query)
        saves = cursor.fetchall()
    return saves
def getMostAttempts(team):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select PlayerSurname,sum(Value) from Match_player_statistics,Match_lineups where (Match_player_statistics.MatchID=Match_lineups.MatchID) and (Match_player_statistics.PlayerID=Match_lineups.ID) and (Match_lineups.Country='%s') and (Match_player_statistics.StatsName='Total Attempts') group by(Match_lineups.ID) order by sum(Value) desc""" %team
        cursor.execute(query)
        attempts = cursor.fetchall()
    return attempts

def getMostTackles(team):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """SELECT PlayerSurname, sum(Value) FROM Match_player_statistics,Match_lineups WHERE (Match_lineups.MatchID=Match_player_statistics.MatchID) AND (Match_lineups.ID=Match_player_statistics.PlayerID) AND (Match_lineups.Country = '%s') AND (Match_player_statistics.StatsName='Tackles') GROUP BY (Match_lineups.ID) ORDER BY SUM(Value) desc""" %team
        cursor.execute(query)
        tackles = cursor.fetchall()
    return tackles
def getMostGoalsGeneral():
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select PlayerSurname,sum(Value) from Match_player_statistics,Match_lineups where (Match_player_statistics.MatchID=Match_lineups.MatchID) and (Match_player_statistics.PlayerID=Match_lineups.ID) and (Match_player_statistics.StatsName='Goals') group by(Match_lineups.ID) order by sum(Value) desc"""
        cursor.execute(query)
        goal = cursor.fetchall()
    return goal
def getMostAssistsGeneral():
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select PlayerSurname,sum(Value) from Match_player_statistics,Match_lineups where (Match_player_statistics.MatchID=Match_lineups.MatchID) and (Match_player_statistics.PlayerID=Match_lineups.ID) and (Match_player_statistics.StatsName='Assists') group by(Match_lineups.ID) order by sum(Value) desc"""
        cursor.execute(query)
        assist = cursor.fetchall()
    return assist
def getMostPassesGeneral():
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select PlayerSurname,sum(Value) from Match_player_statistics,Match_lineups where (Match_player_statistics.MatchID=Match_lineups.MatchID) and (Match_player_statistics.PlayerID=Match_lineups.ID) and (Match_player_statistics.StatsName='Passes completed') group by(Match_lineups.ID) order by sum(Value) desc"""
        cursor.execute(query)
        pas = cursor.fetchall()
    return pas
def getMostYellowGeneral():
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select PlayerSurname,sum(Value) from Match_player_statistics,Match_lineups where (Match_player_statistics.MatchID=Match_lineups.MatchID) and (Match_player_statistics.PlayerID=Match_lineups.ID) and (Match_player_statistics.StatsName='Yellow cards') group by(Match_lineups.ID) order by sum(Value) desc"""
        cursor.execute(query)
        yellow = cursor.fetchall()
    return yellow
def getMostSavesGeneral():
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select PlayerSurname,sum(Value) from Match_player_statistics,Match_lineups where (Match_player_statistics.MatchID=Match_lineups.MatchID) and (Match_player_statistics.PlayerID=Match_lineups.ID) and (Match_player_statistics.StatsName='Saves') group by(Match_lineups.ID) order by sum(Value) desc"""
        cursor.execute(query)
        save = cursor.fetchall()
    return save
def getMostTacklesGeneral():
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """SELECT PlayerSurname,sum(Value) from Match_player_statistics,Match_lineups where(Match_player_statistics.PlayerID=Match_lineups.ID) AND (Match_player_statistics.MatchID=Match_lineups.MatchID) AND (Match_player_statistics.StatsName='Tackles') GROUP BY(Match_player_statistics.MatchID) order by sum(Value) desc"""
        cursor.execute(query)
        tackle = cursor.fetchall()
    return tackle
def getRandomStats(stat):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """SELECT TeamName,MAX(Match_team_statistics.Value) AS MAX_DIST from Match_team_statistics where (Match_team_statistics.StatsName = '%s')"""%stat
        cursor.execute(query)
        randomstats = cursor.fetchall()
    return randomstats
def getRefCards(card):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """SELECT RefereeWebName,SUM(Value) from Match_team_statistics,Match_information WHERE(Match_team_statistics.MatchID = Match_information.MatchID) and (Match_team_statistics.StatsName = '%s') group by Match_information.RefereeWebName order by sum(Value) DESC"""%card
        cursor.execute(query)
        refcard = cursor.fetchall()
    return refcard

def game_info(infomatch):
    info = matchInformation(infomatch)
    return render_template("game_info.html",infomatch=infomatch,info=info)
app.add_url_rule("/game_info/<infomatch>",view_func=game_info)

def matchInformation(match_info):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """SELECT  DISTINCT Event, Minute, TeamName, PlayerName, PlayerSurname from Match_events, Match_information, Match_team_statistics, Match_player_statistics where Match_events.PlayerFromID=Match_player_statistics.PlayerID and Match_events.MatchID=Match_information.MatchID and Match_events.MatchID = "%s" and Match_events.Event = "Goal" and Match_events.TeamFromID = Match_team_statistics.TeamID"""%match_info
        cursor.execute(query)
        goals_in_match = cursor.fetchall()
    return goals_in_match

def statsFantasy(stat):
    with dbapi2.connect('sqlitedb.db') as connection:
        cursor = connection.cursor()
        query = """select Fantasy_team.PlayerSurname,sum(Value) from Match_player_statistics,Match_lineups,Fantasy_team where (Fantasy_team.PlayerSurname=Match_lineups.OfficialSurname) and (Match_player_statistics.MatchID=Match_lineups.MatchID) and (Match_player_statistics.PlayerID=Match_lineups.ID) and (Match_player_statistics.Value='%s') group by(Match_lineups.ID) order by sum(Value) desc""" % stat
        cursor.execute(query)
        values = cursor.fetchall()
    return values
