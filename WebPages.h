#ifndef WEBPAGES_H
#define WEBPAGES_H

#include <Arduino.h>

// Dashboard UI - Optimized for ESP32 Flash storage
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart Farm Pro | AgTech Dashboard</title>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', 'Montserrat', sans-serif;
        }

        :root {
            --obsidian: #0a0e14;
            --charcoal: #1a1f2e;
            --emerald: #10b981;
            --emerald-glow: rgba(16, 185, 129, 0.4);
            --amber: #f59e0b;
            --amber-glow: rgba(245, 158, 11, 0.4);
            --blue-light: #e2e8f0;
            --blue-text: #94a3b8;
            --glass-bg: rgba(30, 41, 59, 0.4);
            --glass-border: rgba(148, 163, 184, 0.1);
            --shadow: 0 8px 32px rgba(0, 0, 0, 0.36);
        }

        body {
            background: linear-gradient(135deg, var(--obsidian) 0%, #1e293b 100%);
            color: var(--blue-light);
            min-height: 100vh;
            padding: 20px;
            overflow-x: hidden;
        }

        .dashboard-header {
            display: flex;
            flex-direction: column;
            align-items: center;
            padding: 20px;
            background: var(--glass-bg);
            backdrop-filter: blur(10px);
            border: 1px solid var(--glass-border);
            border-radius: 20px;
            margin-bottom: 30px;
            box-shadow: var(--shadow);
            text-align: center;
        }

        .logo {
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 10px;
            margin-bottom: 15px;
            width: 100%;
        }

        .logo-icon {
            font-size: 3rem;
            color: var(--emerald);
        }

        .logo-text h1 {
            font-size: 2.2rem;
            font-weight: 800;
            background: linear-gradient(to right, var(--emerald), #34d399, #84cc16);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            letter-spacing: 1px;
            margin-bottom: 5px;
        }

        .logo-text p {
            color: var(--blue-text);
            font-size: 1rem;
            max-width: 600px;
        }

        .status-indicator {
            display: flex;
            align-items: center;
            gap: 10px;
            padding: 10px 25px;
            background: rgba(16, 185, 129, 0.1);
            border-radius: 50px;
            border: 1px solid rgba(16, 185, 129, 0.2);
            margin-top: 10px;
        }

        .status-dot {
            width: 12px;
            height: 12px;
            background-color: var(--emerald);
            border-radius: 50%;
            animation: pulse 2s infinite;
        }

        @keyframes pulse {
            0%, 100% { opacity: 1; }
            50% { opacity: 0.5; }
        }

        .dashboard-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
            gap: 25px;
            margin-bottom: 30px;
        }

        .sensor-card {
            background: var(--glass-bg);
            backdrop-filter: blur(10px);
            border: 1px solid var(--glass-border);
            border-radius: 20px;
            padding: 25px;
            box-shadow: var(--shadow);
            transition: transform 0.3s ease, box-shadow 0.3s ease;
        }

        .sensor-card:hover {
            transform: translateY(-5px);
            box-shadow: 0 12px 40px rgba(0, 0, 0, 0.5);
        }

        .sensor-header {
            display: flex;
            align-items: center;
            justify-content: space-between;
            margin-bottom: 20px;
        }

        .sensor-icon {
            font-size: 1.8rem;
            background: rgba(30, 41, 59, 0.7);
            width: 60px;
            height: 60px;
            display: flex;
            align-items: center;
            justify-content: center;
            border-radius: 15px;
            border: 1px solid var(--glass-border);
        }

        .temp-icon { color: #ef4444; }
        .humidity-icon { color: #3b82f6; }
        .soil-icon { color: #a855f7; }
        .water-icon { color: #0ea5e9; }
        .rain-icon { color: #8b5cf6; }
        .light-icon { color: #f59e0b; }

        .sensor-label {
            text-align: right;
        }

        .sensor-label h3 {
            font-size: 1rem;
            color: var(--blue-text);
            margin-bottom: 5px;
            text-transform: uppercase;
            letter-spacing: 1px;
        }

        .sensor-label p {
            font-size: 0.9rem;
            opacity: 0.7;
        }

        .gauge-container {
            position: relative;
            width: 180px;
            height: 180px;
            margin: 0 auto;
        }

        .gauge-bg {
            fill: none;
            stroke: rgba(30, 41, 59, 0.8);
            stroke-width: 15;
        }

        .gauge-fill {
            fill: none;
            stroke-width: 15;
            stroke-linecap: round;
            transform: rotate(-90deg);
            transform-origin: 50% 50%;
            transition: stroke-dasharray 1s ease;
        }

        .gauge-value {
            position: absolute;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            text-align: center;
        }

        .gauge-value .value {
            font-size: 2.5rem;
            font-weight: 700;
            color: white;
            line-height: 1;
        }

        .gauge-value .unit {
            font-size: 1rem;
            color: var(--blue-text);
            margin-top: 5px;
        }

        .control-panel {
            background: var(--glass-bg);
            backdrop-filter: blur(10px);
            border: 1px solid var(--glass-border);
            border-radius: 20px;
            padding: 30px;
            margin-bottom: 30px;
            box-shadow: var(--shadow);
        }

        .panel-title {
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
            font-size: 1.5rem;
            margin-bottom: 25px;
            color: white;
            text-align: center;
        }

        .panel-title i {
            color: var(--emerald);
        }

        .controls-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));
            gap: 20px;
        }

        .control-btn {
            background: rgba(30, 41, 59, 0.7);
            border: 1px solid var(--glass-border);
            border-radius: 15px;
            padding: 20px 15px;
            color: var(--blue-light);
            font-weight: 600;
            cursor: pointer;
            transition: all 0.3s ease;
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 10px;
        }

        .control-btn:hover {
            background: rgba(30, 41, 59, 0.9);
            border-color: var(--emerald);
            box-shadow: 0 0 20px var(--emerald-glow);
            transform: translateY(-3px);
        }

        .control-btn i {
            font-size: 1.8rem;
        }

        .feed-btn {
            background: rgba(139, 92, 246, 0.1);
            border: 1px solid rgba(139, 92, 246, 0.3);
        }

        .feed-btn:hover {
            border-color: #8b5cf6;
            box-shadow: 0 0 20px rgba(139, 92, 246, 0.4);
        }

        .feed-btn i {
            color: #8b5cf6;
        }

        .watering-btn {
            background: rgba(14, 165, 233, 0.1);
            border: 1px solid rgba(14, 165, 233, 0.3);
        }

        .watering-btn:hover {
            border-color: #0ea5e9;
            box-shadow: 0 0 20px rgba(14, 165, 233, 0.4);
        }

        .watering-btn i {
            color: #0ea5e9;
        }

        .smart-btn {
            grid-column: span 2;
            background: rgba(30, 41, 59, 0.7);
            border: 1px solid rgba(245, 158, 11, 0.3);
            position: relative;
            overflow: hidden;
        }

        .smart-btn.active {
            background: rgba(245, 158, 11, 0.1);
            border-color: var(--amber);
            box-shadow: 0 0 25px var(--amber-glow);
        }

        .smart-btn:hover {
            border-color: var(--amber);
            box-shadow: 0 0 25px var(--amber-glow);
        }

        .lcd-panel {
            background: var(--glass-bg);
            backdrop-filter: blur(10px);
            border: 1px solid var(--glass-border);
            border-radius: 20px;
            padding: 30px;
            box-shadow: var(--shadow);
        }

        .lcd-display {
            background: rgba(15, 23, 42, 0.8);
            border-radius: 15px;
            padding: 20px;
            margin-bottom: 20px;
            border: 1px solid rgba(148, 163, 184, 0.1);
            font-family: 'Courier New', monospace;
            font-size: 1.1rem;
            color: #84cc16;
            text-align: center;
            min-height: 80px;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
        }

        .lcd-label {
            color: var(--blue-text);
            font-size: 0.9rem;
            margin-bottom: 10px;
        }

        .lcd-input-container {
            display: flex;
            gap: 15px;
        }

        .lcd-input {
            flex-grow: 1;
            background: rgba(30, 41, 59, 0.7);
            border: 1px solid var(--glass-border);
            border-radius: 12px;
            padding: 15px 20px;
            color: white;
            font-size: 1rem;
            outline: none;
            transition: border 0.3s ease;
        }

        .lcd-input:focus {
            border-color: var(--emerald);
        }

        .update-btn {
            background: linear-gradient(135deg, var(--emerald), #34d399);
            border: none;
            border-radius: 12px;
            padding: 0 30px;
            color: white;
            font-weight: 600;
            cursor: pointer;
            transition: all 0.3s ease;
        }

        .update-btn:hover {
            transform: translateY(-2px);
            box-shadow: 0 5px 15px rgba(16, 185, 129, 0.4);
        }

        /* Responsive */
        @media (max-width: 768px) {
            .dashboard-header {
                padding: 15px;
            }
            
            .logo-icon {
                font-size: 2.5rem;
            }
            
            .logo-text h1 {
                font-size: 1.8rem;
            }
            
            .controls-grid {
                grid-template-columns: repeat(2, 1fr);
            }
            
            .smart-btn {
                grid-column: span 2;
            }
            
            .lcd-input-container {
                flex-direction: column;
            }
            
            .update-btn {
                padding: 15px;
            }
        }

        @media (max-width: 480px) {
            .dashboard-grid {
                grid-template-columns: 1fr;
            }
            
            .controls-grid {
                grid-template-columns: 1fr;
            }
            
            .smart-btn {
                grid-column: span 1;
            }
            
            .logo-text h1 {
                font-size: 1.5rem;
            }
            
            .logo-text p {
                font-size: 0.9rem;
            }
        }
    </style>
</head>
<body>
    <header class="dashboard-header">
        <div class="logo">
            <div class="logo-icon">
                <i class="fas fa-seedling"></i>
            </div>
            <div class="logo-text">
                <h1>Smart Farm Pro</h1>
                <p>AgTech Monitoring & Control System</p>
            </div>
        </div>
        
        <div class="status-indicator">
            <div class="status-dot"></div>
            <span id="modeStatus">Manual Mode</span>
        </div>
    </header>

    <main class="dashboard-grid">
        <!-- Temperature Card -->
        <div class="sensor-card">
            <div class="sensor-header">
                <div class="sensor-icon temp-icon">
                    <i class="fas fa-thermometer-half"></i>
                </div>
                <div class="sensor-label">
                    <h3>Temperature</h3>
                    <p>DHT11 Sensor</p>
                </div>
            </div>
            <div class="gauge-container">
                <svg viewBox="0 0 200 200">
                    <circle class="gauge-bg" cx="100" cy="100" r="85"></circle>
                    <circle class="gauge-fill" id="temp-gauge" cx="100" cy="100" r="85" stroke="#ef4444"></circle>
                </svg>
                <div class="gauge-value">
                    <div class="value" id="t">--</div>
                    <div class="unit">°C</div>
                </div>
            </div>
        </div>

        <!-- Humidity Card -->
        <div class="sensor-card">
            <div class="sensor-header">
                <div class="sensor-icon humidity-icon">
                    <i class="fas fa-tint"></i>
                </div>
                <div class="sensor-label">
                    <h3>Humidity</h3>
                    <p>Air Moisture Level</p>
                </div>
            </div>
            <div class="gauge-container">
                <svg viewBox="0 0 200 200">
                    <circle class="gauge-bg" cx="100" cy="100" r="85"></circle>
                    <circle class="gauge-fill" id="humidity-gauge" cx="100" cy="100" r="85" stroke="#3b82f6"></circle>
                </svg>
                <div class="gauge-value">
                    <div class="value" id="h">--</div>
                    <div class="unit">%</div>
                </div>
            </div>
        </div>

        <div class="sensor-card">
            <div class="sensor-header">
                <div class="sensor-icon soil-icon">
                    <i class="fas fa-leaf"></i>
                </div>
                <div class="sensor-label">
                    <h3>Soil Moisture</h3>
                    <p>Plant Root Zone</p>
                </div>
            </div>
            <div class="gauge-container">
                <svg viewBox="0 0 200 200">
                    <circle class="gauge-bg" cx="100" cy="100" r="85"></circle>
                    <circle class="gauge-fill" id="soil-gauge" cx="100" cy="100" r="85" stroke="#a855f7"></circle>
                </svg>
                <div class="gauge-value">
                    <div class="value" id="s">--</div>
                    <div class="unit">%</div>
                </div>
            </div>
        </div>

        <!-- Water Tank Card -->
        <div class="sensor-card">
            <div class="sensor-header">
                <div class="sensor-icon water-icon">
                    <i class="fas fa-water"></i>
                </div>
                <div class="sensor-label">
                    <h3>Water Tank</h3>
                    <p>Storage Capacity</p>
                </div>
            </div>
            <div class="gauge-container">
                <svg viewBox="0 0 200 200">
                    <circle class="gauge-bg" cx="100" cy="100" r="85"></circle>
                    <circle class="gauge-fill" id="water-gauge" cx="100" cy="100" r="85" stroke="#0ea5e9"></circle>
                </svg>
                <div class="gauge-value">
                    <div class="value" id="w">--</div>
                    <div class="unit">%</div>
                </div>
            </div>
        </div>

        <div class="sensor-card">
            <div class="sensor-header">
                <div class="sensor-icon rain-icon">
                    <i class="fas fa-cloud-rain"></i>
                </div>
                <div class="sensor-label">
                    <h3>Rain Detection</h3>
                    <p>Precipitation Level</p>
                </div>
            </div>
            <div class="gauge-container">
                <svg viewBox="0 0 200 200">
                    <circle class="gauge-bg" cx="100" cy="100" r="85"></circle>
                    <circle class="gauge-fill" id="rain-gauge" cx="100" cy="100" r="85" stroke="#8b5cf6"></circle>
                </svg>
                <div class="gauge-value">
                    <div class="value" id="r">--</div>
                    <div class="unit">%</div>
                </div>
            </div>
        </div>

        <!-- Light Sensor Card -->
        <div class="sensor-card">
            <div class="sensor-header">
                <div class="sensor-icon light-icon">
                    <i class="fas fa-sun"></i>
                </div>
                <div class="sensor-label">
                    <h3>Light Intensity</h3>
                    <p>Ambient Lighting</p>
                </div>
            </div>
            <div class="gauge-container">
                <svg viewBox="0 0 200 200">
                    <circle class="gauge-bg" cx="100" cy="100" r="85"></circle>
                    <circle class="gauge-fill" id="light-gauge" cx="100" cy="100" r="85" stroke="#f59e0b"></circle>
                </svg>
                <div class="gauge-value">
                    <div class="value" id="li">--</div>
                    <div class="unit">%</div>
                </div>
            </div>
        </div>
    </main>

    <section class="control-panel">
        <h2 class="panel-title"><i class="fas fa-gamepad"></i> Control Panel</h2>
        <div class="controls-grid">
            <button class="control-btn" onclick="ctrl('A')">
                <i class="fas fa-lightbulb"></i>
                <span>LED Control</span>
            </button>
            <button class="control-btn" onclick="ctrl('B')">
                <i class="fas fa-fan"></i>
                <span>Fan Control</span>
            </button>
            
            <button class="control-btn feed-btn" onclick="ctrl('C')">
                <i class="fas fa-paw"></i>
                <span>Animal Feeding</span>
            </button>
            
            <button class="control-btn watering-btn" onclick="ctrl('D')">
                <i class="fas fa-seedling"></i>
                <span>Plant Irrigation</span>
            </button>
            
            <button class="control-btn smart-btn" id="sBtn" onclick="ctrl('smart')">
                <i class="fas fa-brain"></i>
                <span>Smart Mode</span>
            </button>
        </div>
    </section>

    <section class="lcd-panel">
        <h2 class="panel-title"><i class="fas fa-tv"></i> LCD Display Control</h2>
        <div class="lcd-display">
            <div class="lcd-label">Current LCD Message:</div>
            <div id="currentMessage">Farm Online</div>
        </div>
        <div class="lcd-input-container">
            <input type="text" class="lcd-input" id="msgInput" placeholder="Enter message for LCD display...">
            <button class="update-btn" onclick="sendLCD()">Update LCD</button>
        </div>
    </section>

    <script>
        function ctrl(v) { 
            fetch("/set?value=" + v); 
        }
        
        function sendLCD() { 
            let txt = document.getElementById('msgInput').value;
            if (txt.trim() !== "") {
                document.getElementById('currentMessage').textContent = txt;
                fetch("/lcd?text=" + encodeURIComponent(txt));
                document.getElementById('msgInput').value = "";
            }
        }

        function updateGauge(gaugeId, value, maxValue = 100) {
            const gauge = document.getElementById(gaugeId);
            if (!gauge) return;
            
            const circumference = 2 * Math.PI * 85;
            const percentage = Math.min(Math.max(value, 0), maxValue) / maxValue;
            const strokeDasharray = `${circumference * percentage} ${circumference * (1 - percentage)}`;
            
            gauge.style.strokeDasharray = strokeDasharray;
        }

        function updateDashboard(data) {
            document.getElementById('t').textContent = data.t;
            document.getElementById('h').textContent = data.h;
            document.getElementById('s').textContent = data.s;
            document.getElementById('w').textContent = data.w;
            document.getElementById('r').textContent = data.r;
            document.getElementById('li').textContent = data.li;
            
            updateGauge('temp-gauge', data.t, 50);
            updateGauge('humidity-gauge', data.h);
            updateGauge('soil-gauge', data.s);
            updateGauge('water-gauge', data.w);
            updateGauge('rain-gauge', data.r);
            updateGauge('light-gauge', data.li);
            
            const smartBtn = document.getElementById('sBtn');
            const modeStatus = document.getElementById('modeStatus');
            
            if (data.m === "Smart") {
                smartBtn.classList.add('active');
                smartBtn.innerHTML = '<i class="fas fa-brain"></i><span>Smart Mode ON</span>';
                modeStatus.textContent = "Smart Mode Active";
                modeStatus.style.color = "#f59e0b";
            } else {
                smartBtn.classList.remove('active');
                smartBtn.innerHTML = '<i class="fas fa-brain"></i><span>Smart Mode</span>';
                modeStatus.textContent = "Manual Mode";
                modeStatus.style.color = "#10b981";
            }
        }

        setInterval(() => {
            fetch("/data")
                .then(response => response.json())
                .then(data => {
                    updateDashboard(data);
                })
                .catch(error => console.error('Error fetching data:', error));
        }, 1500);

        document.addEventListener('DOMContentLoaded', function() 
        {
            const gaugeIds = ['temp-gauge', 'humidity-gauge', 'soil-gauge', 'water-gauge', 'rain-gauge', 'light-gauge'];
            gaugeIds.forEach(id => updateGauge(id, 0));
            document.getElementById('currentMessage').textContent = "Farm Online";
        });

        document.getElementById('msgInput').addEventListener('keypress', function(e) {
            if (e.key === 'Enter') {
                sendLCD();
            }
        });
    </script>
</body>
</html>
)rawliteral";

#endif